#include "interfaceview.hpp"
#include "../simulation/structure/townhall/townhall.hpp"
#include "../utility/logger/logger.hpp"
#include "../utility/itemtypetostring/itemtypetostring.hpp"

InterfaceView::InterfaceView(){
	if (!m_font.openFromFile("fonts/Pixel.ttf")) {
		defaultLogger.errorLog(true, "font data file failed to open");
	}
}

void InterfaceView::renderStorageItems(sf::RenderWindow& win, Storage& st) {

	const std::vector<Item>& items = st.getItemsView();

	std::string inventory = "Townhall Storage:\n";
	for (int i = 0; i < items.size(); i++) {
		inventory += itemTypeToString(items[i].type) + " " + std::to_string(items[i].count) + "\n";
	}

	static sf::Text text(m_font);
	text.setString(inventory);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color(255, 255, 255, 200));
	win.draw(text);
}

void InterfaceView::renderSimulationStats(sf::RenderWindow& win, Simulation& sim) {
	std::string entityAmount = "Citizens: " + std::to_string(sim.getEntitiesAmount()) + "\n";
	std::string houseAmount = "Houses: " + std::to_string(sim.getHousesCount());
	std::string sum = entityAmount + houseAmount;
	
	static sf::Text text(m_font);
	text.setString(sum);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color(255, 255, 255, 200));
	text.setPosition({ 250,0 });
	win.draw(text);
}

void InterfaceView::render(sf::RenderWindow& win, Simulation& sim, MapSize size) {
	Storage& storage = dynamic_cast<TownHall*>(sim.getSimulationState().getStructure(0))->inv;
	renderStorageItems(win, storage);
	renderSimulationStats(win,sim);
}