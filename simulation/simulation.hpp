#include <vector>
#include "../map/mapData/mapdata.hpp"
#include "../map/mapData/tile.hpp"

class Simulation {
	uint16_t m_mapWidth = 0;
	uint16_t m_mapHeight = 0;
	std::vector<std::vector<TileType>> m_tileGrid = {};

	uint8_t m_tickRate = 20;

	void initTileGrid(MapData&);

public:

	Simulation(MapData& md);
	uint8_t getTickRate(){return m_tickRate;}
	void simulate();
};