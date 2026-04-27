#include <cstdint>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../worldstate/worldstate.hpp"
#include "entitystate/entitystate.hpp"
#include "task/task.hpp"
#include "../type.hpp"

/*
	All that is needed to simulate and render one guy
*/
struct Entity {
	EntityState m_entState;
	ActiveTool m_type = ActiveTool::None;

	std::vector<std::unique_ptr<Task>> m_tasks = {};
	uint16_t m_curTask = 0;

	Entity(const WorldState& wState) : m_entState(wState), m_type(ActiveTool::None) {}
	Entity(const WorldState& wState, uint16_t posX, uint16_t posY, ActiveTool type) :m_entState(wState,posX,posY), m_type(type) {}
	void render(sf::RenderWindow& window) const;
	void sim();
};
