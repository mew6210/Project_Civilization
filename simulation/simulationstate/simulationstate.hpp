#pragma once
#include "../mapsize/mapsize.hpp"
#include "../../map/mapData/tile.hpp"
#include "../../map/mapData/mapdata.hpp"
#include <random>
#include "../structure/structure.hpp"
/*
	Holds everything needed for simulation regarding world state

	Also has a random number generator, so that theres a single generator for n amount of entities

	Is shared by entities, should only be passed by const reference
*/
class SimulationState {

	MapSize mapSize;
	std::vector<std::vector<TileType>> m_tileGrid = {};
	

 	mutable std::mt19937 rng;

	void initTileGrid(const MapData&);
public:

	std::vector<std::unique_ptr<Structure>> m_structures = {};
	
	MapSize getMapSize() const { return mapSize; }
	int getRandInt(int min, int max) const;
	void addStructure(sf::Vector2f, StructureType);
	SimulationState(const MapData&);
};