#include <vector>
#include "../map/mapData/mapdata.hpp"
#include "../map/mapData/tile.hpp"

class Simulation {
	uint16_t m_mapWidth = 0;
	uint16_t m_mapHeight = 0;
	std::vector<std::vector<TileType>> m_tileGrid = {};

	void initTileGrid(MapData&);

public:
	Simulation(MapData& md);
	void simulate();
};