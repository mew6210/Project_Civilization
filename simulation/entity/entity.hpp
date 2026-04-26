#include <cstdint>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../worldstate/worldstate.hpp"
#include "entitystate/entitystate.hpp"
#include "task/task.hpp"

struct Entity {
	EntityState m_entState;

	std::vector<std::unique_ptr<Task>> m_tasks = {};
	uint16_t m_curTask = 0;

	Entity(const WorldState& wState) : m_entState(wState) {}
	Entity(const WorldState& wState, uint16_t posX, uint16_t posY) :m_entState(wState,posX,posY) {}
	void render(sf::RenderWindow& window) const;
	void sim();
};
