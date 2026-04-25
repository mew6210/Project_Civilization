#include "entity.hpp"

void Entity::render(sf::RenderWindow& window) const {
	sf::RectangleShape shape{ sf::Vector2f{4,4} };
	shape.setPosition(sf::Vector2f{ float(m_posX),float(m_posY) });
	shape.setFillColor(sf::Color{ 255,0,0 });
	shape.setOutlineColor(sf::Color{ 255,0,0 });
	window.draw(shape);
	
}

void Entity::sim() {
	if (m_tasks.empty()) {
		m_tasks.push_back(std::make_unique<WanderRandTask>(*this));
	}

	m_tasks[m_curTask]->tick();
}

void WanderRandTask::tick() {
	if (m_actions.empty()) {
		int dx = m_ent.m_wState.getRandInt(-50, 50);
		int dy = m_ent.m_wState.getRandInt(-50, 50);
		int destX = m_ent.m_posX + dx;	//TODO: COULD GO OUT OF BOUNDS
		int destY = m_ent.m_posY + dy;

		m_actions.push_back(std::make_unique<MoveToAction>(m_ent, destX, destY));
	}
	if (m_actions[m_actionStep]->m_isDone) {
		m_actions.pop_back();
		return;
	}
	m_actions[m_actionStep]->tick();
}

//TODO: AI-GENERATED, REPLACE LATER
void MoveToAction::tick() {
	
	int dx = static_cast<int>(m_DestinationX) - static_cast<int>(m_ent.m_posX);
	int dy = static_cast<int>(m_DestinationY) - static_cast<int>(m_ent.m_posY);

	// check if already at destination
	if (dx == 0 && dy == 0) {
		m_isDone = true;
		return; // or mark task finished
	}

	// move on X axis first
	if (dx != 0) {
		m_ent.m_posX += (dx > 0) ? 1 : -1;
	}
	// otherwise move on Y axis
	else if (dy != 0) {
		m_ent.m_posY += (dy > 0) ? 1 : -1;
	}

}