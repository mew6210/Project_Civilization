#include "task.hpp"

/*
	Chooses a place in 50 tiles radius and creates an action to go to that place

	Goes there every tick until its there
*/
void WanderRandTask::tick(EntityState& entState) {
	if (m_actions.empty()) {
		int dx = entState.m_wState.getRandInt(-50, 50);
		int dy = entState.m_wState.getRandInt(-50, 50);
		int destX = entState.m_posX + dx;	//TODO: COULD GO OUT OF BOUNDS
		int destY = entState.m_posY + dy;

		m_actions.push_back(std::make_unique<MoveToAction>(entState, destX, destY));
	}
	if (m_actions[m_actionStep]->m_isDone) {
		m_actions.pop_back();
		return;
	}
	m_actions[m_actionStep]->tick(entState);
}