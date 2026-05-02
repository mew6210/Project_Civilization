#pragma once
#include "../../entitystate/entitystate.hpp"
#include <cstdint>

/*
	Represents a primitive action that an entity can be doing

	Examples: going somewhere, standing somewhere for x amount of ticks
*/
struct Action {
	
	bool m_isDone = false;

	virtual void tick(EntityState&) = 0;
public:
	Action(){}
};

struct MoveToAction : public Action {
	uint16_t m_DestinationX;
	uint16_t m_DestinationY;

	MoveToAction(EntityState& e, uint16_t destinationX, uint16_t destinationY) :
		m_DestinationX(destinationX),
		m_DestinationY(destinationY) {
	}
	void tick(EntityState&) override;
};