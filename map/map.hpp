#pragma once
#include "mapData/mapdata.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

/*
	@brief represents map's texture and needed data to create that texture.
	
	Is initialized with filename that holds required MapData to create texture.

*/
class Map {

	MapData m_data;
	sf::Texture m_texture;

	void initMapData(const std::string&);
	void initTexture();
	void initMap(const std::string&);

public:
	void saveMapData();
	sf::Texture& getTexture() { return m_texture; }

	Map(const std::string& s){
		initMap(s);
	}
};