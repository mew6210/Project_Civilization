#pragma once
#include <cstdint>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include "task/prioritizedtask/prioritizedtask.hpp"
#include "entitystate/entitystate.hpp"
#include "task/task.hpp"

class SimulationState;

/*
	All that is needed to simulate and render one guy
*/
struct Entity {
	mutable EntityState m_entState;

	mutable std::vector<PrioritizedTask> m_tasks = {};
	uint16_t m_curTask = 0;

	Entity(const SimulationState& wState) : m_entState(wState) {}
	Entity(const SimulationState& wState, uint16_t posX, uint16_t posY) :m_entState(wState,posX,posY) {}
	void render(sf::RenderWindow& window) const;
	void sim();
	void delegateTask(PrioritizedTask tsk) const;
};
