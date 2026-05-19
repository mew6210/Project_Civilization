#include "task.hpp"
#include "../../simulationstate/simulationstate.hpp"
#include <iostream>
#include "../../structure/house/house.hpp"
#include "../../../utility/logger/logger.hpp"

/*
	Chooses a place in 50 tiles radius and creates an action to go to that place

	Goes there every tick until its there
*/
void WanderRandTask::tick(EntityState& entState) {
	
	if (isActionsEmpty()) {
		int dx = entState.m_wState.getRandInt(-50, 50);
		int dy = entState.m_wState.getRandInt(-50, 50);
		int destX = entState.m_posX + dx;	//TODO: COULD GO OUT OF BOUNDS
		int destY = entState.m_posY + dy;

		addAction(std::make_unique<MoveToAction>(destX, destY));
	}
	if (getActions()[getActionStep()]->isDone()) {
		isDone(true);
		return;
	}
	getActions()[getActionStep()]->tick(entState);
	
}

GatherFruitBushTask::GatherFruitBushTask(uint16_t bsInd,SimulationState& simState) : m_bushIndex(bsInd) {
	auto townHallPos = simState.getStructure(0)->getPos();
	auto bushTemp = dynamic_cast<Bush*>(simState.getStructure(m_bushIndex));
	
	if (!bushTemp->claim()) isDone(false);

	addAction(std::make_unique<MoveToAction>(uint16_t(bushTemp->getPos().x),uint16_t(bushTemp->getPos().y)));
	addAction(std::make_unique<WaitAction>(bushTemp->getFruitAmount() * 10)); //gather one fruit in half a second
	addAction(std::make_unique<MoveToAction>(uint16_t(townHallPos.x), uint16_t(townHallPos.y))); //go to townhall
	addAction(std::make_unique<DumpToTownHallStorageAction>()); //dump berries to storage

}

void GatherFruitBushTask::unclaimBush(const SimulationState& simState) const {
	auto bushTemp = dynamic_cast<Bush*>(simState.getStructure(m_bushIndex));

	bushTemp->unclaim();
}

ItemType BushTypeToItemType(BushType type) {

	switch (type) {
	case BushType::Strawberry: return ItemType::Strawberry;
	case BushType::Blueberry: return ItemType::Blueberry;
	case BushType::Raspberry: return ItemType::Raspberry;
	case BushType::Null: return ItemType::Null;
	default: return ItemType::Null;
	}

}

Item GatherFruitBushTask::getFruitsFromBush(const SimulationState& simState) const {
	auto bushTemp = dynamic_cast<Bush*>(simState.getStructure(m_bushIndex));

	Item item = Item{ BushTypeToItemType(bushTemp->getBushType()),bushTemp->getFruitAmount()}; 
	bushTemp->clearFruitAmount();
	
	return item;
}

//there HAS to be a better way to do it, but why bother
void GatherFruitBushTask::tick(EntityState& ent) {

	if (!isDone()) {
		if (getActionStep() == 0) {
			if (!getAction(0)->isDone())
				getAction(0)->tick(ent);
			else setActionStep(1);
		}

		if (getActionStep() == 1) {
			if (!getAction(1)->isDone())
				getAction(1)->tick(ent);
			else { 
				unclaimBush(ent.m_wState);
				Item fruits = getFruitsFromBush(ent.m_wState);
				ent.m_haul = fruits;
				setActionStep(2);
			}
		}
		
		if (getActionStep() == 2) {
			if (!getAction(2)->isDone())
				getAction(2)->tick(ent);
			else setActionStep(3);
		}

		if (getActionStep() == 3) {
			if (!getAction(3)->isDone())
				try {
					getAction(3)->tick(ent);
				}
				catch (const std::exception& e) {
					defaultLogger.errorLog("DumpToTownHallStorageAction failed, this should never happen");
					isDone(true);
				}

			else {
				isDone(true);
			}
		}

	}
	
}

//copied 1:1 from bush tick
void GatherWoodTreeTask::tick(EntityState& ent) {

	if (!isDone()) {
		if (getActionStep() == 0) {
			if (!getAction(0)->isDone())
				getAction(0)->tick(ent);
			else setActionStep(1);
		}

		if (getActionStep() == 1) {
			if (!getAction(1)->isDone())
				getAction(1)->tick(ent);
			else {
				unclaimTree(ent.m_wState);
				Item wood = getWoodFromTree(ent.m_wState);
				ent.m_haul = wood;
				setActionStep(2);
			}
		}

		if (getActionStep() == 2) {
			if (!getAction(2)->isDone())
				getAction(2)->tick(ent);
			else setActionStep(3);
		}

		if (getActionStep() == 3) {
			if (!getAction(3)->isDone())
				getAction(3)->tick(ent);
			else {
				isDone(true);
			}
		}

	}

}
//copied 1:1 from unclaimBush
void GatherWoodTreeTask::unclaimTree(const SimulationState& simState) const{

	auto treeTemp = dynamic_cast<Tree*>(simState.getStructure(m_treeIndex));

	treeTemp->unclaim();
}

ItemType TreeTypeToItemType(TreeType treeType){
	switch (treeType){
	case TreeType::Oak:
		return ItemType::Oak;

	case TreeType::Spruce:
		return ItemType::Spruce;

	case TreeType::Birch:
		return ItemType::Birch;

	default:
		return ItemType::Null;
	}
}

//copied 1:1 from removeFruitFromBush
Item GatherWoodTreeTask::getWoodFromTree(const SimulationState& simState) const{
	auto treeTemp = dynamic_cast<Tree*>(simState.getStructure(m_treeIndex));

	//std::cout << "gathered " << +treeTemp->getWoodAmount() << " wood" << " from treeId: " << m_treeIndex << "\n";
	Item item = {TreeTypeToItemType(treeTemp->getTreeType()),treeTemp->getWoodAmount()};
	treeTemp->clearWoodAmount();
	return item;
}

//copied 1:1 from bush ctr
GatherWoodTreeTask::GatherWoodTreeTask(uint16_t treeIndex, SimulationState& simState): m_treeIndex(treeIndex){
	auto townHallPos = simState.getStructure(0)->getPos();
	auto treeTemp = dynamic_cast<Tree*>(simState.getStructure(m_treeIndex));

	if (!treeTemp->claim()) isDone(false);

	addAction(std::make_unique<MoveToAction>(uint16_t(treeTemp->getPos().x), uint16_t(treeTemp->getPos().y)));
	addAction(std::make_unique<WaitAction>(treeTemp->getWoodAmount() * 10)); //gather one wood in half a second
	addAction(std::make_unique<MoveToAction>(uint16_t(townHallPos.x), uint16_t(townHallPos.y)));
	addAction(std::make_unique<DumpToTownHallStorageAction>());
}


GetFoodAndEatTask::GetFoodAndEatTask(SimulationState& simState) {
	auto townHallPos = simState.getStructure(0)->getPos();

	addAction(std::make_unique<MoveToAction>(uint16_t(townHallPos.x), uint16_t(townHallPos.y)));
	addAction(std::make_unique<GetItemFromTownHallStorageAction>(ItemCategory::Food, 10));
	addAction(std::make_unique<ConsumeHaulAction>());
}
void GetFoodAndEatTask::tick(EntityState& ent) {
	
	if (!isDone()) {
		if (getActionStep() == 0) {
			if (!getAction(0)->isDone())
				getAction(0)->tick(ent);
			else setActionStep(1);
		}

		if (getActionStep() == 1) {
			if (!getAction(1)->isDone())
				getAction(1)->tick(ent);
			else {
				auto act = reinterpret_cast<GetItemFromTownHallStorageAction*>(getAction(1));
				if (act->isFound() == false) {	//if u havent found food, dont try to consume it
					isDone(true);
				}
				else {
					setActionStep(2); //else try to consume it
				}
				
			}
		}

		if (getActionStep() == 2) {
			if (!getAction(2)->isDone())
				getAction(2)->tick(ent);
			else isDone(true);
		}
	}
}


HaulMaterialToBuilding::HaulMaterialToBuilding(ItemCategory cat,uint16_t structureId, SimulationState& simState): m_cat(cat), m_structureIndex(structureId) {
	auto townHallPos = simState.getStructure(0)->getPos();
	auto buildingPos = simState.getStructure(m_structureIndex)->getPos();
	
	auto buildingPtr = reinterpret_cast<Buildable*>(simState.getStructure(m_structureIndex));
	buildingPtr->claim();
	addAction(std::make_unique<MoveToAction>(uint16_t(townHallPos.x), uint16_t(townHallPos.y))); //go to townhall
	addAction(std::make_unique<GetItemFromTownHallStorageAction>(cat, 10)); //get items
	addAction(std::make_unique<MoveToAction>(uint16_t(buildingPos.x), uint16_t(buildingPos.y))); //go to building
	addAction(std::make_unique<DumpToBuildingStorageAction>(m_structureIndex)); //insert materials to building storage
}

void HaulMaterialToBuilding::tick(EntityState& ent) {

	if (!isDone()) {
		if (getActionStep() == 0) {
			if (!getAction(0)->isDone())
				getAction(0)->tick(ent);
			else setActionStep(1);
		}

		if (getActionStep() == 1) {
			if (!getAction(1)->isDone())
				getAction(1)->tick(ent);
			else setActionStep(2);
		}

		if (getActionStep() == 2) {
			if (!getAction(2)->isDone())
				getAction(2)->tick(ent);
			else setActionStep(3);
		}

		if (getActionStep() == 3) {
			if (!getAction(3)->isDone())
				getAction(3)->tick(ent);
			else {
				auto buildingPtr = reinterpret_cast<Buildable*>(ent.m_wState.getStructure(m_structureIndex));
				buildingPtr->unclaim();
				isDone(true);
			}
		}

	}
}

GoToHouseAndMate::GoToHouseAndMate(bool birthing,uint16_t stId, SimulationState& simState,uint16_t entId) : m_houseId(stId) {

	auto housePtr = dynamic_cast<House*>(simState.getStructure(stId));
	

	addAction(std::make_unique<MoveToAction>((uint16_t)housePtr->getPos().x, (uint16_t)housePtr->getPos().y));
	addAction(std::make_unique<WaitForMateAction>(stId,birthing,simState,entId));
}

void GoToHouseAndMate::tick(EntityState& entState) {

	if (!isDone()) {
		if (getActionStep() == 0) {
			if (!getAction(0)->isDone())
				getAction(0)->tick(entState);
			else {
				setActionStep(1);

				auto housePtr = dynamic_cast<House*>(entState.m_wState.getStructure(m_houseId));
				housePtr->checkIn(entState.m_id);
			}
		}

		if (getActionStep() == 1) {
			if (!getAction(1)->isDone())
				getAction(1)->tick(entState);
			else {
				auto housePtr = dynamic_cast<House*>(entState.m_wState.getStructure(m_houseId));
				housePtr->unclaim();
				isDone(true);
				auto mateActionPtr = dynamic_cast<WaitForMateAction*>(getAction(1));
				entState.setMatingCooldown();
				if (mateActionPtr->wasSuccessfull() && mateActionPtr->birthingAction()) {
					entState.m_wState.spawnBabyEntity(housePtr->getPos());
				}

			}
		}

	}
}