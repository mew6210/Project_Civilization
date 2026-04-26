#include "task.hpp"

/*
	Chooses a place in 50 tiles radius and creates an action to go to that place

	Goes there every tick until its there
*/
void WanderRandTask::tick() {
	if (m_actions.empty()) {
		int dx = m_entState.m_wState.getRandInt(-50, 50);
		int dy = m_entState.m_wState.getRandInt(-50, 50);
		int destX = m_entState.m_posX + dx;	//TODO: COULD GO OUT OF BOUNDS
		int destY = m_entState.m_posY + dy;

		m_actions.push_back(std::make_unique<MoveToAction>(m_entState, destX, destY));
	}
	if (m_actions[m_actionStep]->m_isDone) {
		m_actions.pop_back();
		return;
	}
	m_actions[m_actionStep]->tick();
}