#pragma once
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "../map/mapData/tile.hpp"
#include "mapsize/mapsize.hpp"
#include "simulationstate/simulationstate.hpp"
#include "../game/inputhandler/activetool.hpp"

/*
	@brief represents simulation state 
	
	@param mapData valid mapdata that will be used to generate tilegrid
*/
class Simulation {
	
	SimulationState m_wState;

	uint8_t m_tickRate = 20;

	void renderEntities(sf::RenderWindow&);
	void renderStructures(sf::RenderWindow&);
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
	SimulationState& getSimulationState() { return m_wState; }

	size_t getEntitiesAmount() const { return m_wState.getEntiesSize(); }
	uint16_t getHousesCount() { return m_wState.getHousesCount(); }

};