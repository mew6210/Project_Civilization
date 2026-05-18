#include "townhall.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "../../../utility/logger/logger.hpp"
#include "../house/house.hpp"

//file-specific globals
namespace {
	constexpr uint8_t k_GatherThresholdAmount = 8;
	constexpr uint8_t k_GatherTaskPriority = 10;
	constexpr sf::Color k_TownHallColor = sf::Color(229, 232, 23);
	constexpr int k_GoEatTaskSatiationLimit = 30;
}

/*
	Currently renders a 1x1 townhall as a 6x6 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void TownHall::render(sf::RenderWindow& win){
	sf::RectangleShape shape{ sf::Vector2f{6,6} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(m_pos);
	shape.setFillColor(k_TownHallColor);

	win.draw(shape);
	inv.renderItemList(win);
}

/*
	finds entity's id in a vector by its generated id 
	
	(usually its entityId +1, but in the future it wont be like that due to entity deaths)
*/
uint16_t TownHall::getEntityVectorIndexByEntityId(uint16_t id) {

	for (uint16_t i = 0; i < m_simState.m_entities.size(); i++) {
		if (id == m_simState.m_entities[i]->m_entState.m_id) return i;
	}

}

/*
	tries to find an entity that is wandering around

	it can return null, because there is a possibility of every entity being busy
*/
std::optional<uint16_t> TownHall::findNotBusyEntityId() {

	uint16_t entityId = 0;
	
	for (const auto& ent : m_simState.m_entities) {

		if (ent->m_tasks.size() == 1) {
			if (ent->m_tasks[0].priority == 0) {		//if it has only one task, and is wandering around
				entityId = ent->m_entState.m_id;
			}
		}
	}

	if (entityId != 0) return entityId;
	else return std::nullopt;
}

/*
	 finds a suitable bush, that is:

	unclaimed, has the most fruit, fruit is more than threshold

	it can return null, because there could be no bushes that suit those requirements
*/
std::optional<uint16_t> TownHall::findBushToGather(uint8_t fruitThreshold) {

	uint8_t maxFruit = 0;
	uint8_t bushIndex = 0;
	uint8_t counter = 0;

	//loop through structures, and find bush with the most fruits
	for (const auto& structure : m_simState.m_structures) {
		if (structure->getType() == StructureType::Bush) { //only check bushes
			
			auto bushPtr = dynamic_cast<Bush*>(structure.get()); //reinterpret structure pointer to a bush pointer
			if (isSuitableBush(maxFruit,fruitThreshold,bushPtr)) { //if its the bigger amount, and bush is not claimed
				maxFruit = bushPtr->getFruitAmount();
				bushIndex = counter;
			}

		}
		counter++;
	}

	if (bushIndex != 0) return bushIndex;
	else return std::nullopt;
}

bool TownHall::isSuitableBush(uint8_t maxFruit, uint8_t fruitThreshold, Bush* bushPtr) const {
	return (bushPtr->getFruitAmount() > maxFruit && !bushPtr->checkClaim() && bushPtr->getFruitAmount() > fruitThreshold);
}

bool TownHall::isSuitableTree(uint8_t maxWood, uint8_t woodThreshold, Tree* treePtr) const {
	return (treePtr->getWoodAmount() > maxWood && !treePtr->checkClaim() && treePtr->getWoodAmount() > woodThreshold);
}

//1:1 copy of findBushToGather
std::optional<uint16_t> TownHall::findTreeToGather(uint8_t woodThreshold) {

	uint8_t maxWood = 0;
	uint8_t treeIndex = 0;
	uint8_t counter = 0;

	//loop through structures, and find tree with the most wood
	for (const auto& structure : m_simState.m_structures) {

		if (structure->getType() == StructureType::Tree) { //only check trees
			auto treePtr = dynamic_cast<Tree*>(structure.get()); //reinterpret structure pointer to a tree pointer
			if (isSuitableTree(maxWood,woodThreshold,treePtr)) { //if its the bigger amount, and tree is not claimed
				maxWood = treePtr->getWoodAmount();
				treeIndex = counter;
			}
		}
		counter++;
	}

	if (treeIndex != 0) return treeIndex;
	else return std::nullopt;
}

/*
	find a grown-enough bush, a not busy entity, and delegate a task to gather that bush to entity
*/
void TownHall::delegateGatherBushTask() {

	auto bushId = findBushToGather(k_GatherThresholdAmount);
	if (!bushId) {
		//std::cout << "no fruits to gather\n"; TODO: ADD TO LOGGER
		return;
	}
	auto entityId = findNotBusyEntityId();
	if (!entityId) {
		//std::cout << "no free entities\n"; TODO: ADD TO LOGGER
		return;
	}
	auto entityIndex = getEntityVectorIndexByEntityId(entityId.value());

	PrioritizedTask tsk{ 
		std::make_unique<GatherFruitBushTask>(
			bushId.value(),
			m_simState),
		k_GatherTaskPriority
	};
	m_simState.m_entities[entityIndex]->delegateTask(std::move(tsk));
	
	auto bushPtr = reinterpret_cast<Bush*>(m_simState.m_structures[bushId.value()].get());
	defaultLogger.infoLog("gather fruit, entID: ", entityId.value(), "strID: ", bushId.value());
}


//1:1 copy of delegateGatherBushTask
void TownHall::delegateGatherWoodTreeTask() {

	auto treeId = findTreeToGather(k_GatherThresholdAmount);
	if (!treeId) {
		//std::cout << "no wood to gather\n"; TODO: ADD TO LOGGER
		return;
	}
	auto entityId = findNotBusyEntityId();
	if (!entityId) {
		//std::cout << "no free entities\n"; TODO: ADD TO LOGGER
		return;
	}
	auto entityIndex = getEntityVectorIndexByEntityId(entityId.value()); //needed, because entityId != entity's index in a vector

	PrioritizedTask tsk{
		std::make_unique<GatherWoodTreeTask>(
			treeId.value(),
			m_simState),
		k_GatherTaskPriority
	};
	m_simState.m_entities[entityIndex]->delegateTask(std::move(tsk));

	auto treePtr = reinterpret_cast<Tree*>(m_simState.m_structures[treeId.value()].get());
	defaultLogger.infoLog("gather wood, entID: ", entityId.value(), "strID: ", treeId.value());
}

std::vector<std::pair<size_t,std::vector<ItemCategory>>> TownHall::getBuildingsAndNeeds() {
	std::vector<std::pair<size_t, std::vector<ItemCategory>>> vec = {};
	for (size_t i = 0; i < m_simState.m_structures.size();i++) {

		if (m_simState.m_structures[i]->getType() == StructureType::Building) {
			auto buildableptr = dynamic_cast<Buildable*>(m_simState.m_structures[i].get());
			if (buildableptr->checkisBuilt()) continue;
			if (buildableptr->isClaimed())    continue;
			vec.push_back({ i,buildableptr->getNeededItems() });
		}

	}
	return vec;
}

std::vector<ItemCategory> TownHall::getCurrentTownHallMaterialsAvailable() {
	std::vector<ItemCategory> vec;

	if (inv.howManyFromCategoryExist(ItemCategory::Wood) > 10) vec.push_back(ItemCategory::Wood);
	if (inv.howManyFromCategoryExist(ItemCategory::Food) > 10) vec.push_back(ItemCategory::Food);
	//probably add stone too later
	return vec;
}

uint16_t TownHall::countBuiltHouses() {
	uint16_t counter = 0;
	for (const auto& st : m_simState.m_structures) {
		if (st->getType() == StructureType::House) 
			counter++;
	}
	return counter;
}

std::optional<std::pair<uint16_t, ItemCategory>> TownHall::findBuildingToBuild() {

	auto buildings = getBuildingsAndNeeds();
	auto available = getCurrentTownHallMaterialsAvailable();

	for (const auto& [id, neededItems] : buildings) {

		for (const auto& catNeeded : neededItems) {
			if (std::count(available.begin(), available.end(), catNeeded) != 0) return std::make_pair(id, catNeeded);
			else continue;
		}
	}
	return std::nullopt;
}

void TownHall::delegateBuildBuildingsTask() {
	if (countBuiltHouses() >= m_simState.m_entities.size()) {
		return;
	}

	auto entityId = findNotBusyEntityId();
	if (!entityId) {
		return;
	}

	auto building = findBuildingToBuild();
	if (!building) {
		return;
	}

	auto entityIndex = getEntityVectorIndexByEntityId(entityId.value()); //needed, because entityId != entity's index in a vector

	PrioritizedTask tsk{
		std::make_unique<HaulMaterialToBuilding>(
			building.value().second,
			building.value().first,
			m_simState
			),
		10
	};
	m_simState.m_entities[entityIndex]->delegateTask(std::move(tsk));

	auto buildingptr = reinterpret_cast<Buildable*>(m_simState.m_structures[building.value().first].get());
	defaultLogger.infoLog("haul to building, entID: ", entityId.value(), "strID: ", building.value().first);
}

uint16_t TownHall::findNotBusyHouse() {

	for (uint16_t i = 0; i < m_simState.m_structures.size();i++) {
		if (m_simState.m_structures[i]->getType() == StructureType::House) {
			auto housePtr = dynamic_cast<House*>(m_simState.m_structures[i].get());
			if(!housePtr->isClaimed())
				return i;
		}
	}
	return 0;
}

std::optional<std::pair<uint16_t, uint16_t>> TownHall::findSuitablePair() {

	std::optional<uint16_t> firstEntity = std::nullopt;
	std::optional<uint16_t> secondEntity = std::nullopt;

	for (const auto& ent : m_simState.m_entities) {

		if (ent->m_tasks.size() == 1) {
			if (ent->m_tasks[0].priority == 0 && !firstEntity.has_value() && ent->m_entState.m_matingCd == 0) {
				firstEntity = ent->m_entState.m_id;
			}
			else if (ent->m_tasks[0].priority == 0 && firstEntity.has_value() && ent->m_entState.m_matingCd == 0) {
				secondEntity = ent->m_entState.m_id;
			}
		}

	}
	if (firstEntity.has_value() && secondEntity.has_value()) {
		return std::make_pair(firstEntity.value(), secondEntity.value());
	}
	else return std::nullopt;
}

void TownHall::delegateMatingTask() {

	auto entIds = findSuitablePair();
	if (!entIds) {
		return;
	}
	auto houseId = findNotBusyHouse();
	if (!houseId) {
		return;
	}
	auto entity1Index = getEntityVectorIndexByEntityId(entIds.value().first);
	auto entity2Index = getEntityVectorIndexByEntityId(entIds.value().second);

	PrioritizedTask tsk1{
		std::make_unique<GoToHouseAndMate>(
			true,
			houseId,
			m_simState,
			entIds.value().first
			),
		20
	};

	PrioritizedTask tsk2{
		std::make_unique<GoToHouseAndMate>(
			false,
			houseId,
			m_simState,
			entIds.value().second
			),
		20
	};

	m_simState.m_entities[entity1Index]->delegateTask(std::move(tsk1));
	m_simState.m_entities[entity2Index]->delegateTask(std::move(tsk2));
	auto housePtr = dynamic_cast<House*>(m_simState.m_structures[houseId].get());
	housePtr->claim();
	defaultLogger.infoLog("mating, 1entID: ", entIds.value().first, " 2entID: ", entIds.value().second," houseId: ", houseId);
}

void TownHall::delegateEatingTasks() {

	for (auto& ent : m_simState.m_entities) {

		if (ent->m_entState.m_satiation < k_GoEatTaskSatiationLimit && ent->m_tasks.size() == 1) {
			if (ent->m_tasks[0].priority == 0) {
				PrioritizedTask tsk = {
					std::make_unique<GetFoodAndEatTask>(m_simState),
					10
				};
				ent->delegateTask(std::move(tsk));
			}
		}

	}

}

/*
	Each tick townhall should evaluate its needs, and delegate tasks to fullfill those needs
*/
void TownHall::tick(){
	
	if (tickCounter % 20 == 0) {
		delegateGatherBushTask();
		delegateGatherWoodTreeTask();
		delegateBuildBuildingsTask();
		handleBuildings();
		delegateEatingTasks();
		delegateMatingTask();
		
	}

	tickCounter++;
}

void TownHall::addStartingItems() {
	inv.insertItems(Item{ ItemType::Blueberry,30 },true);
	inv.insertItems(Item{ ItemType::Strawberry,30 },true);
	inv.insertItems(Item{ ItemType::Raspberry,30 },true);
}

void TownHall::handleBuildings() {
	queueBuildings();
}

void TownHall::queueBuildings() {

	if (inv.howManyFromCategoryExist(ItemCategory::Wood) > 30 
		&& m_BuildingsScheduled < 2) {
		
		m_buildingQueue.push_back(std::make_unique<Buildable>(BuildableType::House, getSuitableHousePosition()));
		m_BuildingsScheduled++;
		defaultLogger.infoLog("delegated building a house");
	}

}


//AI GENERATED
sf::Vector2f TownHall::getSuitableHousePosition()
{
	constexpr float HOUSE_RADIUS = 8.f;      // approximate house size
	constexpr float REQUIRED_GAP = 5.f;
	constexpr float MIN_DISTANCE = HOUSE_RADIUS * 2.f + REQUIRED_GAP;

	constexpr float SEARCH_STEP = 10.f;
	constexpr float MAX_SEARCH_RADIUS = 500.f;

	const float worldWidth = m_simState.getMapSize().m_width;
	const float worldHeight = m_simState.getMapSize().m_height;

	// Collect existing structure positions
	std::vector<sf::Vector2f> positions;

	for (auto& structure : m_simState.m_structures)
	{
		positions.push_back(structure->m_pos);
	}

	auto isValidPosition = [&](const sf::Vector2f& pos)
		{
			// Bounds check
			if (pos.x < 0 || pos.y < 0 ||
				pos.x > worldWidth || pos.y > worldHeight)
			{
				return false;
			}

			// Distance check
			for (const auto& other : positions)
			{
				float dx = pos.x - other.x;
				float dy = pos.y - other.y;

				float distSq = dx * dx + dy * dy;

				if (distSq < MIN_DISTANCE * MIN_DISTANCE)
				{
					return false;
				}
			}

			return true;
		};

	// Spiral/radial search
	for (float radius = SEARCH_STEP;
		radius <= MAX_SEARCH_RADIUS;
		radius += SEARCH_STEP)
	{
		for (float angle = 0.f; angle < 360.f; angle += 15.f)
		{
			float rad = angle * 3.14159265f / 180.f;

			sf::Vector2f candidate(
				m_pos.x + std::cos(rad) * radius,
				m_pos.y + std::sin(rad) * radius
			);

			if (isValidPosition(candidate))
			{
				return candidate;
			}
		}
	}

	// fallback
	return m_pos;
}

TownHall::TownHall(sf::Vector2f pos, SimulationState& simState): Structure(pos),m_simState(simState) {
	addStartingItems();
}