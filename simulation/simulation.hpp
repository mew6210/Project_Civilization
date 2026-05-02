#include <vector>

#include "../map/mapData/tile.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "mapsize/mapsize.hpp"
#include "worldstate/worldstate.hpp"
#include "entity/entity.hpp"
#include "../game/ActiveTool/ActiveTool.hpp"

/*
	@brief represents simulation state 
	
	@param mapData valid mapdata that will be used to generate tilegrid
*/
class Simulation {
	
	std::vector<Entity> m_entities = {};
	WorldState m_wState;

	uint8_t m_tickRate = 20;

	void renderEntities(sf::RenderWindow&);
	void renderStructures(sf::RenderWindow&);
public:
	
	Simulation(const MapData& md);
	uint8_t getTickRate() const { return m_tickRate;}
	void simulate();
	void render(sf::RenderWindow&);
	void spawnAt(sf::Vector2f pos, ActiveTool type);
};