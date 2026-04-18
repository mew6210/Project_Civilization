#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../map.hpp"

/*
	@brief Represents map's sprite used for drawing the map.

	Initialized with a Map class, with a valid texture used to create the sprite.

*/
class MapView {

	sf::Sprite m_sprite;

public:
	MapView(Map& m) : m_sprite(m.getTexture()) {}
	void drawMap(sf::RenderWindow&);
};