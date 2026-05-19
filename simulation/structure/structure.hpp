#include <SFML/Graphics/RenderWindow.hpp>
#pragma once
enum class StructureType {
	House,
	Quarry,
	Farm,
	TownHall,
	Bush,
	Tree,
	Building,
	Null
};

class Structure {
	sf::Vector2f m_pos;

public:
	virtual void render(sf::RenderWindow&) = 0;
	virtual void tick() = 0;
	virtual StructureType getType() const = 0;
	virtual ~Structure() = default;
	Structure(sf::Vector2f pos);
	sf::Vector2f getPos() const { return m_pos; }
};
