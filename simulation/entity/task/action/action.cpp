#include "action.hpp"
#include "../../entitystate/entitystate.hpp"
#include "../../../simulationstate/simulationstate.hpp"
#include "../../../structure/townhall/townhall.hpp"
#include <iostream>
#include "../../../../utility/logger/logger.hpp"

void MoveToAction::tick(EntityState& entState) {

	int dx = static_cast<int>(m_DestinationX) - static_cast<int>(entState.m_posX);
	int dy = static_cast<int>(m_DestinationY) - static_cast<int>(entState.m_posY);

	if (dx == 0 && dy == 0) {
		m_isDone = true;
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
	else m_isDone = true;
}

void DumpToStorageAction::tick(EntityState& ent) {
	auto townHallPos = ent.m_wState.m_structures[0]->m_pos;
	uint16_t townHallPosX = townHallPos.x;
	uint16_t townHallPosY = townHallPos.y;

	if (ent.m_posX != townHallPosX){
		m_isDone = true;
		defaultLogger.errorLog(false, "townhall Position and dumpToSTorageAction x axis does not match");
		return;
	}
	if (ent.m_posY != townHallPosY){
		m_isDone = true;
		defaultLogger.errorLog(false, "townhall Position and dumpToSTorageAction y axis does not match");
		return;
	}

	auto townHallPtr = reinterpret_cast<TownHall*>(ent.m_wState.m_structures[0].get());

	townHallPtr->inv.insertItems(Item{ent.m_haul.type,ent.m_haul.count});
	ent.m_haul = {};
	m_isDone = true;
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

void GetItemFromStorageAction::tick(EntityState& ent) {

	auto townhallPtr= dynamic_cast<TownHall*>(ent.m_wState.m_structures[0].get());

	if (m_itemCategory != ItemCategory::Specific) {
		
		auto res = townhallPtr->inv.requestCategory(ent, m_itemCategory, m_count);
		if (!res) {
			defaultLogger.warningLog("Entity couldn't find enough of: ", ItemCategoryToString(m_itemCategory), " ", m_count);
			m_isDone = true;
			return;
		}
		else {
			m_isDone = true;
			m_isFound = true;
			return;
		}

	}

}

namespace {
	constexpr int foodSatiation = 10; //to be changed
}

void ConsumeHaulAction::tick(EntityState& ent) {

	uint32_t foodAmount = ent.m_haul.count;

	if (ent.m_haul.type == ItemType::Blueberry ||
		ent.m_haul.type == ItemType::Strawberry ||
		ent.m_haul.type == ItemType::Raspberry
		) {
		
		ent.m_satiation += foodAmount * foodSatiation;
		ent.m_haul = Item{ ItemType::Null,0 };
		
		defaultLogger.infoLog("entId: ",ent.m_id," eaten food, current satiation: ",ent.m_satiation," current hp: ",ent.m_health);
		m_isDone = true;
	}
	else {
		defaultLogger.warningLog("entity tried to eat something uneatable");
		m_isDone = true;
	}
}

GetItemFromStorageAction::GetItemFromStorageAction(ItemCategory itemCategory, uint64_t count): 
	m_itemCategory(itemCategory),
	m_count(count) {}
GetItemFromStorageAction::GetItemFromStorageAction(ItemType itemType, uint64_t count): 
	m_itemCategory(ItemCategory::Specific),
	m_specificType(itemType),
	m_count(count){}