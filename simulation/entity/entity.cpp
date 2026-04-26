#include "entity.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void Entity::render(sf::RenderWindow& window) const {
	sf::RectangleShape shape{ sf::Vector2f{4,4} };
	shape.setPosition(sf::Vector2f{ float(m_entState.m_posX),float(m_entState.m_posY) });
	shape.setFillColor(sf::Color{ 255,0,0 });
	shape.setOutlineColor(sf::Color{ 255,0,0 });
	window.draw(shape);
	
}

void Entity::sim() {
	if (m_tasks.empty()) {
		m_tasks.push_back(std::make_unique<WanderRandTask>(m_entState));
	}

	m_tasks[m_curTask]->tick();
}