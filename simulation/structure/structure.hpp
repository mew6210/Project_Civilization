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
	StructureType m_type = StructureType::Null;
	sf::Vector2f m_pos;
	virtual void render(sf::RenderWindow&) = 0;
	virtual void tick() = 0;

	Structure(sf::Vector2f pos);
	void setType(StructureType type) { m_type = type; }
	StructureType getType() const { return m_type; }
};
