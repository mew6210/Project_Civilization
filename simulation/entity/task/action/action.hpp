#include "../../entitystate/entitystate.hpp"
#include <cstdint>

/*
	Represents a primitive action that an entity can be doing

	Examples: going somewhere, standing somewhere for x amount of ticks
*/
struct Action {
	EntityState& m_entState;
	bool m_isDone = false;

	virtual void tick() = 0;
public:
	Action(EntityState& e) :m_entState(e) {}
};

struct MoveToAction : public Action {
	uint16_t m_DestinationX;
	uint16_t m_DestinationY;

	MoveToAction(EntityState& e, uint16_t destinationX, uint16_t destinationY) :
		Action(e),
		m_DestinationX(destinationX),
		m_DestinationY(destinationY) {
	}
	void tick() override;
};