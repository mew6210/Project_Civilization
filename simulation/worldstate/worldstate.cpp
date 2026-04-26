#include "worldstate.hpp"


WorldState::WorldState(const MapData& md) : rng(std::random_device{}()) {
	mapSize.m_height = md.getHeight();
	mapSize.m_width = md.getWidth();

	initTileGrid(md);
}

/*
	@brief creates a 2-dimensional NxM vector from a 1-dimensional N vector.
*/
void WorldState::initTileGrid(const MapData& mData) {

	for (size_t i = 0; i < mData.getHeight(); i++) {
		std::vector<TileType> row = {};
		for (size_t j = 0; j < mData.getWidth(); j++) {
			row.push_back(mData.getTile(i, j));
		}

		m_tileGrid.push_back(row);
	}
}

int WorldState::getRandInt(int min, int max) const {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}