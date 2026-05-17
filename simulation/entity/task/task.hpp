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
	Item getFruitsFromBush(const SimulationState& simState) const;
public:

	GatherFruitBushTask(uint16_t bsInd,SimulationState&);
};

class GatherWoodTreeTask : public Task {
	uint16_t m_treeIndex;

	void tick(EntityState& entState) override;
	void unclaimTree(const SimulationState& simState) const;
	Item getWoodFromTree(const SimulationState& simState) const;
public:
	GatherWoodTreeTask(uint16_t treeIndex, SimulationState&);
};

class GetFoodAndEatTask : public Task {
	void tick(EntityState& entState) override;
public:
	GetFoodAndEatTask(SimulationState&);
};

class HaulMaterialToBuilding : public Task {
	void tick(EntityState& entState) override;
	ItemCategory m_cat;
	uint16_t m_structureIndex;

public:
	HaulMaterialToBuilding(ItemCategory,uint16_t, SimulationState&);
};

class GoToHouseAndMate : public Task {
	void tick(EntityState& entState) override;
	uint16_t m_houseId;
public:
	GoToHouseAndMate(bool birthing, uint16_t stId, SimulationState& simState, uint16_t entId);
};