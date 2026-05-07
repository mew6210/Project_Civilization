#include "townhall.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

/*
	Currently renders a 1x1 townhall as a 6x6 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void TownHall::render(sf::RenderWindow& win){
	sf::RectangleShape shape{ sf::Vector2f{6,6} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(m_pos);
	shape.setFillColor(sf::Color(229, 232, 23));

	win.draw(shape);
}

uint16_t TownHall::getEntityVectorIndexByEntityId(uint16_t id) {

	for (uint16_t i = 0; i < m_simState.m_entities.size(); i++) {
		if (id == m_simState.m_entities[i].m_entState.m_id) return i;
	}

}

std::optional<uint16_t> TownHall::findNotBusyEntityId() {

	uint16_t entityId = 0;
	
	for (const auto& ent : m_simState.m_entities) {

		if (ent.m_tasks.size() == 1) {
			if (ent.m_tasks[0].priority == 0) {		//if it has only one task, and is wandering around
				entityId = ent.m_entState.m_id;
			}
		}
	}

	if (entityId != 0) return entityId;
	else return std::nullopt;
}

std::optional<uint16_t> TownHall::findBushToGather(uint8_t fruitThreshold) {

	uint8_t maxFruit = 0;
	uint8_t bushIndex = 0;

	uint8_t counter = 0;

	//loop through structures, and find bush with the most fruits
	for (const auto& structure : m_simState.m_structures) {

		if (structure->getType() == StructureType::Bush) { //only check bushes
			auto bushPtr = dynamic_cast<Bush*>(structure.get()); //reinterpret structure pointer to a bush pointer
			if (bushPtr->getFruitAmount() > maxFruit && !bushPtr->checkClaim() && bushPtr->getFruitAmount() > fruitThreshold) { //if its the bigger amount, and bush is not claimed
				maxFruit = bushPtr->getFruitAmount();
				bushIndex = counter;
			}
		}
		counter++;
	}

	if (bushIndex != 0) return bushIndex;
	else return std::nullopt;
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
			if (treePtr->getWoodAmount() > maxWood && !treePtr->checkClaim() && treePtr->getWoodAmount() > woodThreshold) { //if its the bigger amount, and tree is not claimed
				maxWood = treePtr->getWoodAmount();
				treeIndex = counter;
			}
		}
		counter++;
	}

	if (treeIndex != 0) return treeIndex;
	else return std::nullopt;
}

void TownHall::delegateGatherBushTask() {

	auto bushId = findBushToGather(3);
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
		10
	};
	m_simState.m_entities[entityIndex].delegateTask(std::move(tsk));
	
	auto bushPtr = reinterpret_cast<Bush*>(m_simState.m_structures[bushId.value()].get());
	std::cout << "gathering fruits delegated, entityID: "<<entityId.value()<<" bushID: "<<bushId.value()<<" fruitCount: "<<+bushPtr->getFruitAmount()<<"\n";
}

//1:1 copy of delegateGatherBushTask
void TownHall::delegateGatherWoodTreeTask() {

	auto treeId = findTreeToGather(3);
	if (!treeId) {
		//std::cout << "no wood to gather\n"; TODO: ADD TO LOGGER
		return;
	}
	auto entityId = findNotBusyEntityId();
	if (!entityId) {
		//std::cout << "no free entities\n"; TODO: ADD TO LOGGER
		return;
	}
	auto entityIndex = getEntityVectorIndexByEntityId(entityId.value());

	PrioritizedTask tsk{
		std::make_unique<GatherWoodTreeTask>(
			treeId.value(),
			m_simState),
		10
	};
	m_simState.m_entities[entityIndex].delegateTask(std::move(tsk));

	auto treePtr = reinterpret_cast<Tree*>(m_simState.m_structures[treeId.value()].get());
	std::cout << "gathering wood delegated, entityID: " << entityId.value() << " treeID: " << treeId.value() << " woodCount: " << +treePtr->getWoodAmount() << "\n";
}

void TownHall::tick(){
	
	if (tickCounter % 20 ==0) {
		delegateGatherBushTask();
		delegateGatherWoodTreeTask();
	}

	//delegating tasks, for now its doing nothing
	tickCounter++;
}

TownHall::TownHall(sf::Vector2f pos, SimulationState& simState): Structure(pos),m_simState(simState) {}