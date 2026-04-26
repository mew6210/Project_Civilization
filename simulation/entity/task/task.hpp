#include <vector>
#include "../entitystate/entitystate.hpp"
#include "action/action.hpp"

/*
	Represents a job that an entity can be doing.

	Examples: cut tree, gather fruits, wander randomly

	Those jobs are broken down into more primitive actions
*/
struct Task {
	EntityState& m_entState;
	std::vector<std::unique_ptr<Action>> m_actions;
	uint8_t m_actionStep = 0;
	virtual void tick() = 0;
	Task(EntityState& e) :m_entState(e) {}
};

class WanderRandTask : public Task {
	using Task::Task; //copies a constructor from task
	void tick() override;
};
