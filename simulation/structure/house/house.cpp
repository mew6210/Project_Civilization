#include "house.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

/*
	Currently renders a 1x1 house as a 4x4 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void House::render(sf::RenderWindow& win) {
	sf::RectangleShape shape{ sf::Vector2f{4,4} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(m_pos);
	shape.setFillColor(sf::Color::Black);

	win.draw(shape);
}

void House::tick(){}

House::House(sf::Vector2f pos): Structure(pos) {}

void House::checkIn(uint16_t id){
	m_visitorsIds.push_back(id);
}

void House::checkOut(uint16_t id) {
	auto it = std::find(m_visitorsIds.begin(), m_visitorsIds.end(), id);
	if(it!=m_visitorsIds.end())
		m_visitorsIds.erase(it);
}