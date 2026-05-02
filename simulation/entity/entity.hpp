#include <cstdint>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../simulationstate/simulationstate.hpp"
#include "entitystate/entitystate.hpp"
#include "task/task.hpp"

/*
	All that is needed to simulate and render one guy
*/
struct Entity {
	EntityState m_entState;

	std::vector<std::unique_ptr<Task>> m_tasks = {};
	uint16_t m_curTask = 0;

	Entity(const SimulationState& wState) : m_entState(wState) {}
	Entity(const SimulationState& wState, uint16_t posX, uint16_t posY) :m_entState(wState,posX,posY) {}
	void render(sf::RenderWindow& window) const;
	void sim();
};
