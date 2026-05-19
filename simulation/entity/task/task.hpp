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
class Task {
	bool m_isDone = false;
	uint8_t m_actionStep = 0;
	std::vector<std::unique_ptr<Action>> m_actions;
public:
	
	bool isActionsEmpty() { return m_actions.empty(); }
	void addAction(std::unique_ptr<Action> action) {m_actions.push_back(std::move(action));}
	std::vector<std::unique_ptr<Action>>& getActions() {return m_actions;}
	Action* getAction(size_t i) { return m_actions[i].get();}
	
	uint8_t getActionStep() const { return m_actionStep; }
	void setActionStep(uint8_t t) { m_actionStep = t; }
	
	bool isDone() const { return m_isDone; }
	void isDone(bool b) { m_isDone = b; }
	
	virtual void tick(EntityState& entState) = 0;
	virtual ~Task() = default;
};

class WanderRandTask : public Task {
public:
	using Task::Task; //copies a constructor from task
	void tick(EntityState& entState) override;
};

class GatherFruitBushTask : public Task {
	uint16_t m_bushIndex;
	void unclaimBush(const SimulationState& simState) const;
	Item getFruitsFromBush(const SimulationState& simState) const;
public:

	void tick(EntityState& entState) override;
	GatherFruitBushTask(uint16_t bsInd,SimulationState&);
};

class GatherWoodTreeTask : public Task {
	uint16_t m_treeIndex;

	void unclaimTree(const SimulationState& simState) const;
	Item getWoodFromTree(const SimulationState& simState) const;
public:
	void tick(EntityState& entState) override;
	GatherWoodTreeTask(uint16_t treeIndex, SimulationState&);
};

class GetFoodAndEatTask : public Task {
public:
	void tick(EntityState& entState) override;
	GetFoodAndEatTask(SimulationState&);
};

class HaulMaterialToBuilding : public Task {
	ItemCategory m_cat;
	uint16_t m_structureIndex;

public:
	void tick(EntityState& entState) override;
	HaulMaterialToBuilding(ItemCategory,uint16_t, SimulationState&);
};

class GoToHouseAndMate : public Task {
	uint16_t m_houseId;
public:
	void tick(EntityState& entState) override;
	GoToHouseAndMate(bool birthing, uint16_t stId, SimulationState& simState, uint16_t entId);
};