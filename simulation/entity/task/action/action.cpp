#include "action.hpp"
#include "../../entitystate/entitystate.hpp"

//TODO: AI-GENERATED, REPLACE LATER
void MoveToAction::tick() {

	int dx = static_cast<int>(m_DestinationX) - static_cast<int>(m_entState.m_posX);
	int dy = static_cast<int>(m_DestinationY) - static_cast<int>(m_entState.m_posY);

	// check if already at destination
	if (dx == 0 && dy == 0) {
		m_isDone = true;
		return; // or mark task finished
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