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
class Entity {
public:

	EntityState m_entState;
	//making this private, would mean making a getter which would need to copy since PrioritizedTask has a unique_ptr, thats why its left public
	std::vector<PrioritizedTask> m_tasks = {}; 

	Entity(SimulationState& wState) : m_entState(wState) {}
	Entity(SimulationState& wState, uint16_t posX, uint16_t posY) :m_entState(wState,posX,posY) {}
	Entity(SimulationState& wState, uint16_t posX, uint16_t posY, uint32_t matingCd) :m_entState(wState, posX, posY) { m_entState.m_matingCd = matingCd; }
	void render(sf::RenderWindow& window) const;
	void sim();
	void delegateTask(PrioritizedTask tsk);

private:

	uint64_t m_tickCounter = 0;
	uint16_t m_curTask = 0;
	void doCurrentTask();
	void updateStats();
	void evalDeath();
	bool isHungry()const;
	bool isStarving()const;
	bool isFull()const;
	
};
