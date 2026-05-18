#include <vector>

#include "../map/mapData/tile.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "mapsize/mapsize.hpp"
#include "simulationstate/simulationstate.hpp"
#include "../game/ActiveTool/ActiveTool.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

/*
	@brief represents simulation state 
	
	@param mapData valid mapdata that will be used to generate tilegrid
*/
class Simulation {
	
	SimulationState m_wState;

	uint8_t m_tickRate = 20;
	sf::Font font;
	sf::Text text;

	void renderEntities(sf::RenderWindow&);
	void renderStructures(sf::RenderWindow&);
	void renderEntityAmount(sf::RenderWindow&);
	void simulateEntities();
	void simulateStructures();
	void promoteBuildings();
	void promoteBuilding(size_t);
public:

	Simulation(const MapData& md);
	uint8_t getTickRate() const { return m_tickRate;}
	void simulate();
	void render(sf::RenderWindow&);
	void spawnAt(sf::Vector2f pos, ActiveTool type);
};