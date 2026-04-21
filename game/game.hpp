#include <SFML/Graphics/RenderWindow.hpp>
#include "../map/map.hpp"
#include "../map/mapView/mapview.hpp"
#include "../simulation/simulation.hpp"


class Game {
	Map map;
	MapView mView;
	Simulation sim;

	void render(sf::RenderWindow&);
	void advanceSimulation(sf::Clock&, float&, const float&);
	void handleInput(sf::RenderWindow&);
public:
	Game(const std::string&);
	void mainLoop();
};