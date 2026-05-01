#include "entity.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

/*
	Currently renders a 1x1 entity based on a type as a 4x4 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void Entity::render(sf::RenderWindow& window) const {
	sf::RectangleShape shape{ sf::Vector2f{4,4} };
	shape.setPosition(sf::Vector2f{ float(m_entState.m_posX),float(m_entState.m_posY) });
	shape.setFillColor(sf::Color::Red);

	window.draw(shape);
}

void Entity::sim() {
		if (m_tasks.empty()) {
			m_tasks.push_back(std::make_unique<WanderRandTask>());
		}

		if (m_curTask < m_tasks.size()) {
			m_tasks[m_curTask]->tick(m_entState);
		}
	}