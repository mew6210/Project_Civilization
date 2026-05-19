#include "simulationstate.hpp"
#include "../structure/bush/bush.hpp"
#include "../structure/tree/tree.hpp"
#include "../structure/townhall/townhall.hpp"
#include "../../utility/logger/logger.hpp"

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

std::string tiletypetostring(TileType t) {

	switch (t) {
	case TileType::FertileSoil: return "FertileSoil";
	case TileType::SemiFertileSoil: return "SemiFertileSoil";
	case TileType::TreeSoil: return "TreeSoil";
	case TileType::NotFertileSoil: return "NotFertileSoil";
	default: return "should never happen";
	}
}

void SimulationState::addStructure(sf::Vector2f pos, StructureType type,TileType tile) {

	if (type == StructureType::Bush) {
		int variant = std::uniform_int_distribution<int>(0, 2)(rng);
		BushType type = bushTypeFromInt(variant);

		uint8_t fruitLimit = 30;
		uint8_t ticksNeededToGrow = 100;

		switch (tile) {
		case TileType::FertileSoil: { fruitLimit *= 2.f; ticksNeededToGrow *= 0.5f; } break;
		case TileType::SemiFertileSoil: { fruitLimit *= 0.7f; ticksNeededToGrow *= 1.3f; } break;
		case TileType::TreeSoil: { fruitLimit *= 0.7f; ticksNeededToGrow *= 1.3f; } break;
		case TileType::NotFertileSoil: { fruitLimit *= 0.2f; ticksNeededToGrow *= 1.5f; } break;
		}


		m_structures.push_back(std::make_unique<Bush>(pos, type,ticksNeededToGrow,fruitLimit));
	}
	if (type == StructureType::Tree){
		int variant = std::uniform_int_distribution<int>(0, 2)(rng);
		TreeType type = treeTypeFromInt(variant);
		uint8_t woodLimit = 30;
		uint8_t ticksNeededToGrow = 100;

		switch (tile) {
		case TileType::FertileSoil: { woodLimit *= 2.f; ticksNeededToGrow *= 0.5f; } break;
		case TileType::SemiFertileSoil: { woodLimit *= 0.7f; ticksNeededToGrow *= 1.3f; } break;
		case TileType::TreeSoil: { woodLimit *= 2.f; ticksNeededToGrow *= 0.5f; } break;
		case TileType::NotFertileSoil: { woodLimit *= 0.2f; ticksNeededToGrow *= 1.5f; } break;
		}

		m_structures.push_back(std::make_unique<Tree>(pos,type,ticksNeededToGrow,woodLimit));
	}
	if (type == StructureType::TownHall) m_structures.push_back(std::make_unique<TownHall>(pos, *this));
}

void SimulationState::addBuilding(sf::Vector2f pos, BuildableType type) {

	m_structures.push_back(std::make_unique<Buildable>(type,pos));

}

void SimulationState::spawnBabyEntity(sf::Vector2f pos) {
	defaultLogger.infoLog("baby born");
	m_entities.push_back(std::make_unique<Entity>(*this, (uint16_t)pos.x, (uint16_t)pos.y,300));
}
TileType SimulationState::getTile(const uint16_t& row, const uint16_t& col) const {
	return m_tileGrid[col][row];
}