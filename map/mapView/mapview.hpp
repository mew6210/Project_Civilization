#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../map.hpp"

/*
	@brief Represents map's sprite used for drawing the map.

	@param Map map with a valid texture
*/
class MapView {

	sf::Sprite m_sprite;

public:
	MapView(Map& m) : m_sprite(m.getTexture()) {}
	void drawMap(sf::RenderWindow&);
};