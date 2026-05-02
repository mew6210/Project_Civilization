#pragma once
#include <cstdint>

class SimulationState;

/*
	Holds variables that are needed for simulating an entity

	Is passed to stuff like Task or Action by a reference
*/
struct EntityState {
	const uint32_t m_id = 0;	//TODO: ADD MORE STUFF LIKE AGE, NAME, HUNGER, GENDER
	uint16_t m_posX = 0;
	uint16_t m_posY = 0;
	bool isBusy = false;
	const SimulationState& m_wState;

	EntityState(const SimulationState& wState) : m_wState(wState),m_id(++ID) {}
	EntityState(const SimulationState& wState,uint16_t posX,uint16_t posY) : m_wState(wState),m_posX(posX),m_posY(posY),m_id(++ID) {}

private:
	static uint32_t ID;
};