#pragma once
#include <memory>
#include <vector>
#include "../entitystate/entitystate.hpp"
#include "action/action.hpp"
#include "../../structure/bush/bush.hpp"
#include "../../structure/tree/tree.hpp"

/*
	Represents a job that an entity can be doing.

	Examples: cut tree, gather fruits, wander randomly

	Those jobs are broken down into more primitive actions
*/
struct Task {
	bool m_isDone = false;
	std::vector<std::unique_ptr<Action>> m_actions;
	uint8_t m_actionStep = 0;
	virtual void tick(EntityState& entState) = 0;
};

class WanderRandTask : public Task {
	using Task::Task; //copies a constructor from task
	void tick(EntityState& entState) override;
};

class GatherFruitBushTask : public Task {
	uint16_t m_bushIndex;
	void tick(EntityState& entState) override;
	void unclaimBush(const SimulationState& simState) const;
	void removeFruitsFromBush(const SimulationState& simState) const;
public:

	GatherFruitBushTask(uint16_t bsInd,SimulationState&);
};

class GatherWoodTreeTask : public Task {
	uint16_t m_treeIndex;

	void tick(EntityState& entState) override;
	void unclaimTree(const SimulationState& simState) const;
	void removeWoodFromTree(const SimulationState& simState) const;
public:
	GatherWoodTreeTask(uint16_t treeIndex, SimulationState&);
};