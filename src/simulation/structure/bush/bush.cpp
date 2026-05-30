#include "bush.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <limits>


namespace {

	constexpr sf::Color k_BushColor = sf::Color(180, 80, 150);
}

/*
	Currently renders a 1x1 bush as a 4x4 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void Bush::render(sf::RenderWindow& win) {
	
	sf::RectangleShape shape{ sf::Vector2f{4,4} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(getPos());
	shape.setFillColor(k_BushColor);

	win.draw(shape);
}

/*
	grows fruit on a bush, up to a point
*/
void Bush::tick(){
	if (m_tickCounter % m_ticksNeededToGrow == 0) {
		if (m_fruitCount < m_fruitLimit) {
			++m_fruitCount;
		}
	}

	m_tickCounter++;
}

Bush::Bush(sf::Vector2f pos,BushType bushType): Structure(pos),m_BushType(bushType){}
Bush::Bush(sf::Vector2f pos, BushType bushType,uint8_t ticksToGrow,uint8_t fruitLimit) 
	: Structure(pos), m_BushType(bushType),m_ticksNeededToGrow(ticksToGrow),m_fruitLimit(fruitLimit) {}

bool Bush::claim() {
	if (m_isClaimed) return false;
	else { 
		m_isClaimed = true;
		return true;
	}
}