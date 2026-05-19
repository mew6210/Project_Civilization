#include "action.hpp"
#include "../../entitystate/entitystate.hpp"
#include "../../../simulationstate/simulationstate.hpp"
#include "../../../structure/townhall/townhall.hpp"
#include <iostream>
#include "../../../../utility/logger/logger.hpp"
#include "../../../structure/house/house.hpp"

void MoveToAction::tick(EntityState& entState) {

	int dx = static_cast<int>(m_DestinationX) - static_cast<int>(entState.m_posX);
	int dy = static_cast<int>(m_DestinationY) - static_cast<int>(entState.m_posY);

	if (dx == 0 && dy == 0) {
		isDone(true);
		return;
	}

	// move on X axis first
	if (dx != 0) {
		entState.m_posX += (dx > 0) ? 1 : -1;
	}
	// otherwise move on Y axis
	else if (dy != 0) {
		entState.m_posY += (dy > 0) ? 1 : -1;
	}

}

void WaitAction::tick(EntityState&) {
	if (m_curTick < m_tickAmount) {
		m_curTick++;
	}
	else isDone(true);
}

void DumpToTownHallStorageAction::tick(EntityState& ent) {
	auto townHallPos = ent.m_wState.getStructure(0)->m_pos;
	uint16_t townHallPosX = townHallPos.x;
	uint16_t townHallPosY = townHallPos.y;

	if (ent.m_posX != townHallPosX){
		isDone(true);
		defaultLogger.errorLog(false, "townhall Position and dumpToSTorageAction x axis does not match");
		return;
	}
	if (ent.m_posY != townHallPosY){
		isDone(true);
		defaultLogger.errorLog(false, "townhall Position and dumpToSTorageAction y axis does not match");
		return;
	}

	auto townHallPtr = reinterpret_cast<TownHall*>(ent.m_wState.getStructure(0));

	townHallPtr->inv.insertItems(Item{ent.m_haul.type,ent.m_haul.count},false);
	ent.m_haul = {};
	isDone(true);
}

constexpr std::string_view ItemCategoryToString(ItemCategory category) {
	switch (category) {
	case ItemCategory::Food:
		return "Food";

	case ItemCategory::Material:
		return "Material";

	case ItemCategory::Specific:
		return "Specific";

	case ItemCategory::Null:
		return "Null";

	default:
		return "Unknown";
	}
}

void GetItemFromTownHallStorageAction::tick(EntityState& ent) {

	auto townhallPtr= dynamic_cast<TownHall*>(ent.m_wState.getStructure(0));

	if (m_itemCategory != ItemCategory::Specific) {
		
		auto res = townhallPtr->inv.requestCategory(ent, m_itemCategory, m_count);
		if (!res) {
			defaultLogger.warningLog("Entity couldn't find enough of: ", ItemCategoryToString(m_itemCategory), " ", m_count);
			isDone(true);
			return;
		}
		else {
			isDone(true);
			m_isFound = true;
			return;
		}

	}

}

namespace {
	constexpr int foodSatiation = 18; //to be changed
}

void ConsumeHaulAction::tick(EntityState& ent) {

	uint32_t foodAmount = ent.m_haul.count;

	if (ent.m_haul.type == ItemType::Blueberry ||
		ent.m_haul.type == ItemType::Strawberry ||
		ent.m_haul.type == ItemType::Raspberry
		) {
		
		ent.m_satiation += foodAmount * foodSatiation;
		ent.m_haul = Item{ ItemType::Null,0 };
		
		//defaultLogger.infoLog("entId: ",ent.m_id," eaten food, current satiation: ",ent.m_satiation," current hp: ",ent.m_health);
		isDone(true);
	}
	else {
		defaultLogger.warningLog("entity tried to eat something uneatable");
		isDone(true);
	}
}

GetItemFromTownHallStorageAction::GetItemFromTownHallStorageAction(ItemCategory itemCategory, uint64_t count): 
	m_itemCategory(itemCategory),
	m_count(count) {}
GetItemFromTownHallStorageAction::GetItemFromTownHallStorageAction(ItemType itemType, uint64_t count): 
	m_itemCategory(ItemCategory::Specific),
	m_specificType(itemType),
	m_count(count){}


DumpToBuildingStorageAction::DumpToBuildingStorageAction(uint16_t id): m_structureIndex(id){}

void DumpToBuildingStorageAction::tick(EntityState& ent) {

	auto structureptr = ent.m_wState.getStructure(m_structureIndex);
	if (structureptr->getType() != StructureType::Building) {
		defaultLogger.warningLog("tried to insert materials to not a building");
		isDone(true);
		return;
	}

	auto buildingptr = dynamic_cast<Buildable*>(structureptr);
	buildingptr->insertMaterials(ent);
	isDone(true);
}

void WaitForMateAction::tick(EntityState& ent) {

	static auto housePtr = dynamic_cast<House*>(ent.m_wState.getStructure(m_houseIndex));
	
	if (!housePtr->isClaimed()) {
		housePtr->checkOut(ent.m_id);
		//defaultLogger.infoLog("mating assumed successfull");
		housePtr->unclaim();
		m_wasSuccessfull = true;
		isDone(true);
		return;
	}
	if (housePtr->getVisitorsAmount() > 1) {
		isDone(true);
		m_wasSuccessfull = true;
		housePtr->unclaim();
		housePtr->checkOut(ent.m_id);
		return;
	}

	if (m_tickCounter > 600) {
		isDone(true);
		housePtr->unclaim();
		housePtr->checkOut(ent.m_id);
		return;
	}

	m_tickCounter++;
}

WaitForMateAction::WaitForMateAction(uint16_t stIndex,bool birthing,SimulationState& simState,uint16_t entityId): m_houseIndex(stIndex),m_birthingAction(birthing){}