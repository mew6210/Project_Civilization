#include "townhall.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

/*
	Currently renders a 1x1 townhall as a 6x6 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void TownHall::render(sf::RenderWindow& win){
	sf::RectangleShape shape{ sf::Vector2f{6,6} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(m_pos);
	shape.setFillColor(sf::Color(229, 232, 23));

	win.draw(shape);
}

void TownHall::tick(){
	//delegating tasks, for now its doing nothing
}

TownHall::TownHall(sf::Vector2f pos, const SimulationState& simState): Structure(pos),m_simState(simState) {}