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
	uint64_t m_tickCounter = 0;
	mutable std::vector<PrioritizedTask> m_tasks = {};
	uint16_t m_curTask = 0;

	bool m_isAcceptingTasks = true;

	Entity(SimulationState& wState) : m_entState(wState) {}
	Entity(SimulationState& wState, uint16_t posX, uint16_t posY) :m_entState(wState,posX,posY) {}
	Entity(SimulationState& wState, uint16_t posX, uint16_t posY, uint32_t matingCd) :m_entState(wState, posX, posY) { m_entState.m_matingCd = matingCd; }
	void render(sf::RenderWindow& window) const;
	void sim();
	void delegateTask(PrioritizedTask tsk, bool) const;
	

private:
	void addHungryTask();
	void doCurrentTask();
	void updateStats();
	void addTasks();
	void evalDeath();

	void addTasksWhenSome();
	void addTasksWhenNone();
	void handleIsAcceptingTasks();
	bool isHungry();
	bool isStarving();
	bool isFull();
};
