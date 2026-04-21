#include "simulation.hpp"
#include <iostream>

void Simulation::simulate() {
	std::cout << "simulation ran\n";
}

Simulation::Simulation(MapData& md) {
	m_mapWidth = md.getWidth();
	m_mapHeight = md.getHeight();

	initTileGrid(md);
}

void Simulation::initTileGrid(MapData& mData) {

	for (size_t i = 0; i < mData.getHeight(); i++) {
		std::vector<TileType> row = {};
		for (size_t j = 0; j < mData.getWidth(); j++) {
			row.push_back(mData.getTile(i,j));
		}

		m_tileGrid.push_back(row);
	}
}