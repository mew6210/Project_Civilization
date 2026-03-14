#pragma once
#include "mapData/mapdata.hpp"
#include <string>

class Map {

	MapData mapData;
	
public:
	void loadMapData(const std::string&);
	void saveMapData();
};