#include "action.hpp"
#include "../../entitystate/entitystate.hpp"

void MoveToAction::tick() {

	int dx = static_cast<int>(m_DestinationX) - static_cast<int>(m_entState.m_posX);
	int dy = static_cast<int>(m_DestinationY) - static_cast<int>(m_entState.m_posY);

	if (dx == 0 && dy == 0) {
		m_isDone = true;
		return;
	}

	// move on X axis first
	if (dx != 0) {
		m_entState.m_posX += (dx > 0) ? 1 : -1;
	}
	// otherwise move on Y axis
	else if (dy != 0) {
		m_entState.m_posY += (dy > 0) ? 1 : -1;
	}

}