#pragma once
#include "mapData/mapdata.hpp"
#include <string>

class Map {

	MapData data;
	
public:
	void loadMapData(const std::string&);
	void saveMapData();
};