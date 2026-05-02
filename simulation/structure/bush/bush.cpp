#include "bush.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

/*
	Currently renders a 1x1 bush as a 4x4 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void Bush::render(sf::RenderWindow& win) {
	
	sf::RectangleShape shape{ sf::Vector2f{4,4} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(m_pos);
	shape.setFillColor(sf::Color::Magenta);

	win.draw(shape);
}

void Bush::tick(){
	if (m_tickCounter % 100 == 0) {
		if (m_fruitCount < std::numeric_limits<uint8_t>::max()) {
			++m_fruitCount;
		}
	}

	m_tickCounter++;
}

Bush::Bush(sf::Vector2f pos): Structure(pos){
	setType(StructureType::Bush);
}