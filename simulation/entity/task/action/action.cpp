#include "action.hpp"
#include "../../entitystate/entitystate.hpp"

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