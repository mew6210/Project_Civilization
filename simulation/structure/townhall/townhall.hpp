#include "../structure.hpp"
#include "../../simulationstate/simulationstate.hpp"

class TownHall : public Structure {

	const SimulationState& m_simState;
	//Inventory inv = {};
public:
	void render(sf::RenderWindow&) override;
	void tick() override;
	TownHall(sf::Vector2f, const SimulationState&);
};