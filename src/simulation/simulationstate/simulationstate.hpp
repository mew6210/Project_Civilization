#pragma once
#include <random>
#include "../mapsize/mapsize.hpp"
#include "../../map/mapData/tile.hpp"
#include "../../map/mapData/mapdata.hpp"
#include "../structure/structure.hpp"
#include "../entity/entity.hpp"
#include "../structure/buildable/buildable.hpp"

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
	std::vector<std::unique_ptr<Structure>> m_structures = {};
	std::vector<std::unique_ptr<Entity>> m_entities = {};

public:
	//structure-related
	Structure* getStructure(uint16_t t) const { return m_structures[t].get(); }
	std::unique_ptr<Structure>& getStructureReference(uint16_t t) {return m_structures[t];}
	void addStructure(std::unique_ptr<Structure> s) { m_structures.push_back(std::move(s)); }
	std::vector<std::unique_ptr<Structure>>& getStructures() { return m_structures; }

	//entity-related
	Entity* getEntity(uint16_t t) { return m_entities[t].get(); }
	void addEntity(std::unique_ptr<Entity> ent) { m_entities.push_back(std::move(ent)); }
	void reserveEntities(uint16_t count) { m_entities.reserve(count); }
	std::vector<std::unique_ptr<Entity>>& getEntities() { return m_entities; }

	//other
	TileType getTile(const uint16_t& row, const uint16_t& col) const;
	MapSize getMapSize() const { return mapSize; }
	int getRandInt(int min, int max) const;
	void addStructure(sf::Vector2f, StructureType, TileType);
	SimulationState(const MapData&);
	void addBuilding(sf::Vector2f, BuildableType);
	void spawnBabyEntity(sf::Vector2f);
	uint16_t getHousesCount();
};
