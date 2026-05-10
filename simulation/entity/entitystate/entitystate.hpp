#pragma once
#include <cstdint>
#include "../../item/item.hpp"

class SimulationState;

/*
	Holds variables that are needed for simulating an entity

	Is passed to stuff like Task or Action by a reference
*/
struct EntityState {
	const uint32_t m_id = 0;	//TODO: ADD MORE STUFF LIKE AGE, NAME, HUNGER, GENDER
	uint16_t m_posX = 0;
	uint16_t m_posY = 0;
	
	bool m_isBusy = false;
	Item m_haul;

	SimulationState& m_wState;

	uint64_t m_health = 100;
	uint64_t m_satiation = 150;
	bool m_isDead = false;
	

	EntityState(SimulationState& wState) : m_wState(wState),m_id(++ID) {}
	EntityState(SimulationState& wState,uint16_t posX,uint16_t posY) : m_wState(wState),m_posX(posX),m_posY(posY),m_id(++ID) {}

private:
	static uint32_t ID;
};