#include "entity.hpp"
#include <algorithm>
#include <SFML/Graphics/RectangleShape.hpp>

namespace {
	constexpr int k_HungerTickDecreaseCount = 60;
}

/*
	Currently renders a 1x1 entity based on a type as a 4x4 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void Entity::render(sf::RenderWindow& window) const {
	sf::RectangleShape shape{ sf::Vector2f{4,4} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(sf::Vector2f{ float(m_entState.m_posX),float(m_entState.m_posY) });
	shape.setFillColor(sf::Color::Red);

	window.draw(shape);
}

void Entity::doCurrentTask() {
	if (!m_tasks[0].task->m_isDone) {
		m_tasks[0].task->tick(m_entState);
	}
	else m_tasks.pop_back();
}

void Entity::updateStats() {

	if (m_tickCounter % k_HungerTickDecreaseCount == 0 && m_entState.m_satiation != 0) m_entState.m_satiation--;
	if (m_entState.m_satiation == 0 && m_entState.m_health != 0) m_entState.m_health--;
	if (m_entState.m_health == 0) m_entState.m_isDead = true;

	m_tickCounter++;
}

void Entity::sim() {
		
	if (m_tasks.empty()) m_tasks.push_back({std::make_unique<WanderRandTask>(),0});
	
	doCurrentTask();
	updateStats();
}

void Entity::delegateTask(PrioritizedTask tsk) const {

	if (m_tasks.size() == 1) {
		if (m_tasks[0].priority == 0) {
			m_tasks.erase(m_tasks.begin());
		}
	}

	m_tasks.push_back(std::move(tsk));

	std::sort(m_tasks.begin(), m_tasks.end(), [](const PrioritizedTask& a, const PrioritizedTask& b) {
		return a.priority > b.priority;
		});
}