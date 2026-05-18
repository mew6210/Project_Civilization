#include <SFML/Graphics/RenderWindow.hpp>
#include "../map/map.hpp"
#include "../map/mapView/mapview.hpp"
#include "../simulation/simulation.hpp"
#include "handleinput/handleinput.hpp"
#include "../utility/logger/logger.hpp"

/*
	@brief represents everything that is needed to start a game
	@param filepath path to a file that holds valid mapdata
*/
class Game {
	Map map;
	MapView mView;
	Simulation sim;
	ActiveTool currentTool = ActiveTool::None;
	float m_timeScale = 1.0f;

	void render(sf::RenderWindow&);
	void advanceSimulation(sf::Clock&, float&, const float&);
	void handleInput(sf::RenderWindow&);
	void checkTooltipInput();
public:
	Game(const std::string&);
	void mainLoop();
};