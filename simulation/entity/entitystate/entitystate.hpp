#pragma once
#include <cstdint>
#include "../../worldstate/worldstate.hpp"

struct EntityState {
	uint16_t m_posX = 0;
	uint16_t m_posY = 0;
	const WorldState& m_wState;

	EntityState(const WorldState& wState): m_wState(wState){}
	EntityState(const WorldState& wState,uint16_t posX,uint16_t posY) : m_wState(wState),m_posX(posX),m_posY(posY) {}
};