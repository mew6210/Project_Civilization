#pragma once
#include <cstdint>
#include "tile.hpp"
#include <vector>

class MapData {

	uint16_t width;
	uint16_t height;
	std::vector<TileType> data;


};