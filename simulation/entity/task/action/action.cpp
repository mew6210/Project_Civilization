#include "action.hpp"
#include "../../entitystate/entitystate.hpp"
#include "../../../simulationstate/simulationstate.hpp"
#include "../../../structure/townhall/townhall.hpp"
#include <iostream>

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
		std::cout << "something big fucked up";
		return;
	}
	if (ent.m_posY != townHallPosY){
		m_isDone = true;
		std::cout << "something big fucked up";
		return;
	}

	auto townHallPtr = reinterpret_cast<TownHall*>(ent.m_wState.m_structures[0].get());

	townHallPtr->inv.insertItems(Item{ent.m_haul.type,ent.m_haul.count});
	ent.m_haul = {};
	m_isDone = true;
}