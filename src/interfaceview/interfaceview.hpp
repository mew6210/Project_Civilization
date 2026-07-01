#include <SFML/Graphics/RenderWindow.hpp>
#include "../simulation/simulation.hpp"

class InterfaceView {
	sf::Font m_font;
	
	void renderStorageItems(sf::RenderWindow& win, Storage& st);
	void renderSimulationStats(sf::RenderWindow& win, Simulation& sim);
public:
	void render(sf::RenderWindow&, Simulation&, MapSize);
	InterfaceView();
};