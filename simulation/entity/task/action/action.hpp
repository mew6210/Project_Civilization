#pragma once
#include "../../entitystate/entitystate.hpp"
#include <cstdint>

/*
	Represents a primitive action that an entity can be doing

	Examples: going somewhere, standing somewhere for x amount of ticks
*/
class Action {
	
	bool m_isDone = false;

public:
	virtual void tick(EntityState&) = 0;
	bool isDone() const { return m_isDone; }
	void isDone(bool b) { m_isDone = b; }
	Action(){}
};

class MoveToAction : public Action {
	uint16_t m_DestinationX;
	uint16_t m_DestinationY;
public:
	MoveToAction(uint16_t destinationX, uint16_t destinationY) :
		m_DestinationX(destinationX),
		m_DestinationY(destinationY) {
	}
	void tick(EntityState&) override;
};

class WaitAction : public Action {
	uint64_t m_tickAmount;
	uint64_t m_curTick = 0;
public:
	WaitAction(uint64_t tickAmount):m_tickAmount(tickAmount){}
	void tick(EntityState&) override;
};

class DumpToTownHallStorageAction : public Action {	//TODO: assumes that u just dump everything u have, will probably have to be changed later
public:
	void tick(EntityState&) override;
};

class DumpToBuildingStorageAction : public Action {
	uint16_t m_structureIndex;
public:
	void tick(EntityState&)override;
	DumpToBuildingStorageAction(uint16_t);
};

class GetItemFromTownHallStorageAction : public Action {
	
	ItemCategory m_itemCategory;
	ItemType m_specificType;
	uint64_t m_count;
	bool m_isFound = false;
public:
	GetItemFromTownHallStorageAction(ItemCategory, uint64_t);
	GetItemFromTownHallStorageAction(ItemType, uint64_t);
	bool isFound() const { return m_isFound; }
	void tick(EntityState&) override;
};

class ConsumeHaulAction : public Action {
public:
	void tick(EntityState&) override;
};

class WaitForMateAction : public Action {
	uint64_t m_tickCounter = 0;
	uint16_t m_houseIndex = 0;
	bool m_wasSuccessfull = false;
	bool m_birthingAction = false;

public:
	void tick(EntityState&) override;
	bool wasSuccessfull() const {return m_wasSuccessfull;}
	bool birthingAction() const { return m_birthingAction; }
	WaitForMateAction(uint16_t stIndex, bool birthing, SimulationState& simState, uint16_t entityId);
};