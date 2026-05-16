#include "simulationstate.hpp"
#include "../structure/bush/bush.hpp"
#include "../structure/tree/tree.hpp"
#include "../structure/townhall/townhall.hpp"

SimulationState::SimulationState(const MapData& md) : rng(std::random_device{}()) {
	mapSize.m_height = md.getHeight();
	mapSize.m_width = md.getWidth();

	initTileGrid(md);
}

/*
	@brief creates a 2-dimensional NxM vector from a 1-dimensional N vector.
*/
void SimulationState::initTileGrid(const MapData& mData) {

	for (size_t i = 0; i < mData.getHeight(); i++) {
		std::vector<TileType> row = {};
		for (size_t j = 0; j < mData.getWidth(); j++) {
			row.push_back(mData.getTile(i, j));
		}

		m_tileGrid.push_back(row);
	}
}

int SimulationState::getRandInt(int min, int max) const {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

BushType bushTypeFromInt(int value) {
	switch (value) {
	case 0: return BushType::Strawberry;
	case 1: return BushType::Blueberry;
	case 2: return BushType::Raspberry;
	default: return BushType::Null;
	}
}

TreeType treeTypeFromInt(int value) {
	switch (value) {
	case 0: return TreeType::Oak;
	case 1: return TreeType::Spruce;
	case 2: return TreeType::Birch;
	default: return TreeType::Null;
	}
}

void SimulationState::addStructure(sf::Vector2f pos, StructureType type) {

	if (type == StructureType::Bush) {
		int variant = std::uniform_int_distribution<int>(0, 2)(rng);
		BushType type = bushTypeFromInt(variant);

		m_structures.push_back(std::make_unique<Bush>(pos, type));
	}
	if (type == StructureType::Tree){
		int variant = std::uniform_int_distribution<int>(0, 2)(rng);
		TreeType type = treeTypeFromInt(variant);

		m_structures.push_back(std::make_unique<Tree>(pos,type));
	}
	if (type == StructureType::TownHall) m_structures.push_back(std::make_unique<TownHall>(pos, *this));
}

void SimulationState::addBuilding(sf::Vector2f pos, BuildableType type) {

	m_structures.push_back(std::make_unique<Buildable>(type,pos));

}