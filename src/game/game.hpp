#include <SFML/Graphics/RenderWindow.hpp>
#include <format>
#include <iostream>
#include "../map/map.hpp"
#include "../map/mapView/mapview.hpp"
#include "../simulation/simulation.hpp"
#include "../utility/logger/logger.hpp"
#include "../interfaceview/interfaceview.hpp"
#include "inputhandler/inputhandler.hpp"

/*
	@brief represents everything that is needed to start a game
	@param filepath path to a file that holds valid mapdata
*/
class Game {
	Map map;
	Simulation sim;
	InputHandler inHandler;

	MapView mView;
	InterfaceView iView;

	void render(sf::RenderWindow&);
	void advanceSimulation(sf::Clock&, float&, const float&);
	void printUserManual();
public:
	Game(const std::string&);
	void mainLoop();
};