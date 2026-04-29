#include <SFML/Graphics/RenderWindow.hpp>
#include "../map/map.hpp"
#include "../map/mapView/mapview.hpp"
#include "../simulation/simulation.hpp"
#include "ActiveTool/ActiveTool.hpp"

/*
	@brief represents everything that is needed to start a game
	@param filepath path to a file that holds valid mapdata
*/
class Game {
	Map map;
	MapView mView;
	Simulation sim;
	ActiveTool currentTool = ActiveTool::None;

	void render(sf::RenderWindow&);
	void advanceSimulation(sf::Clock&, float&, const float&);
	void handleInput(sf::RenderWindow&);
	void checkTooltipInput();
public:
	Game(const std::string&);
	void mainLoop();
};