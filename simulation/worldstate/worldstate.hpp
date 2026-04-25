#pragma once
#include "../mapsize/mapsize.hpp"
#include "../../map/mapData/tile.hpp"
#include "../../map/mapData/mapdata.hpp"
#include <random>

class WorldState {

	MapSize mapSize;
	std::vector<std::vector<TileType>> m_tileGrid = {};
 	mutable std::mt19937 rng;

	void initTileGrid(const MapData&);
public:

	MapSize getMapSize() const { return mapSize; }
	int getRandInt(int min, int max) const;

	WorldState(const MapData&);
};