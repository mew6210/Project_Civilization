#include <SFML/Graphics/RenderWindow.hpp>
#pragma once
enum class StructureType {
	TownHall,
	Bush,
	Tree,
	House,
	Null
};

class Structure {
public:
	sf::Vector2f m_pos;
	virtual void render(sf::RenderWindow&) = 0;
	virtual void tick() = 0;
	virtual StructureType getType() const = 0;

	Structure(sf::Vector2f pos);
};
