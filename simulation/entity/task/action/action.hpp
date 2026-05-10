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

	MoveToAction(uint16_t destinationX, uint16_t destinationY) :
		m_DestinationX(destinationX),
		m_DestinationY(destinationY) {
	}
	void tick(EntityState&) override;
};

struct WaitAction : public Action {
	uint64_t m_tickAmount;
	uint64_t m_curTick = 0;

	WaitAction(uint64_t tickAmount):m_tickAmount(tickAmount){}
	void tick(EntityState&) override;
};

struct DumpToStorageAction : public Action {	//TODO: assumes that u just dump everything u have, will probably have to be changed later
	void tick(EntityState&) override;
};

struct GetItemFromStorageAction : public Action {
	
	ItemCategory m_itemCategory;
	ItemType m_specificType;
	uint64_t m_count;

	GetItemFromStorageAction(ItemCategory, uint64_t);
	GetItemFromStorageAction(ItemType, uint64_t);
	void tick(EntityState&) override;
public:
	bool m_isFound = false;
};

struct ConsumeHaulAction : public Action {
	void tick(EntityState&) override;
};