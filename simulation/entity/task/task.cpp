#include "task.hpp"
#include "../../simulationstate/simulationstate.hpp"
#include <iostream>

/*
	Chooses a place in 50 tiles radius and creates an action to go to that place

	Goes there every tick until its there
*/
void WanderRandTask::tick(EntityState& entState) {
	
	if (m_actions.empty()) {
		int dx = entState.m_wState.getRandInt(-50, 50);
		int dy = entState.m_wState.getRandInt(-50, 50);
		int destX = entState.m_posX + dx;	//TODO: COULD GO OUT OF BOUNDS
		int destY = entState.m_posY + dy;

		m_actions.push_back(std::make_unique<MoveToAction>(destX, destY));
	}
	if (m_actions[m_actionStep]->m_isDone) {
		m_isDone = true;
		return;
	}
	m_actions[m_actionStep]->tick(entState);
	
}

GatherFruitBushTask::GatherFruitBushTask(uint16_t bsInd,SimulationState& simState) : m_bushIndex(bsInd) {
	auto townHallPos = simState.m_structures[0]->m_pos;
	auto bushTemp = dynamic_cast<Bush*>(simState.m_structures[m_bushIndex].get());
	
	if (!bushTemp->claim()) m_isDone = false;

	m_actions.push_back(std::make_unique<MoveToAction>(uint16_t(bushTemp->m_pos.x),uint16_t(bushTemp->m_pos.y)));
	m_actions.push_back(std::make_unique<WaitAction>(bushTemp->getFruitAmount() * 10)); //gather one fruit in half a second
	m_actions.push_back(std::make_unique<MoveToAction>(uint16_t(townHallPos.x), uint16_t(townHallPos.y))); //go to townhall
	m_actions.push_back(std::make_unique<DumpToStorageAction>()); //dump berries to storage

}

void GatherFruitBushTask::unclaimBush(const SimulationState& simState) const {
	auto bushTemp = dynamic_cast<Bush*>(simState.m_structures[m_bushIndex].get());

	bushTemp->unclaim();
}

ItemType BushTypeToItemType(BushType type) {

	switch (type) {
	case BushType::Strawberry: return ItemType::Strawberry;
	case BushType::Blueberry: return ItemType::Blueberry;
	case BushType::Raspberry: return ItemType::Raspberry;
	case BushType::Null: return ItemType::Blueberry;
	}

}

Item GatherFruitBushTask::getFruitsFromBush(const SimulationState& simState) const {
	auto bushTemp = dynamic_cast<Bush*>(simState.m_structures[m_bushIndex].get());

	Item item = Item{ BushTypeToItemType(bushTemp->getBushType()),bushTemp->getFruitAmount()}; //TODO: Make it work for other bushes types

	std::cout << "gathered " << +bushTemp->getFruitAmount()<<" fruit" <<" from bushId: "<<m_bushIndex << "\n";
	bushTemp->clearFruitAmount();
	
	return item;
}

//there HAS to be a better way to do it, but why bother
void GatherFruitBushTask::tick(EntityState& ent) {

	if (!m_isDone) {
		if (m_actionStep == 0) {
			if (!m_actions[0]->m_isDone)
				m_actions[0]->tick(ent);
			else m_actionStep = 1;
		}

		if (m_actionStep == 1) {
			if (!m_actions[1]->m_isDone)
				m_actions[1]->tick(ent);
			else { 
				unclaimBush(ent.m_wState);
				Item fruits = getFruitsFromBush(ent.m_wState);
				ent.m_haul = fruits;
				m_actionStep = 2;
			}
		}
		
		if (m_actionStep == 2) {
			if (!m_actions[2]->m_isDone)
				m_actions[2]->tick(ent);
			else m_actionStep = 3;
		}

		if (m_actionStep == 3) {
			if (!m_actions[3]->m_isDone)
				m_actions[3]->tick(ent);
			else {
				m_isDone = true;
			}
		}

	}
	
}

//copied 1:1 from bush tick
void GatherWoodTreeTask::tick(EntityState& ent) {

	if (!m_isDone) {
		if (m_actionStep == 0) {
			if (!m_actions[0]->m_isDone)
				m_actions[0]->tick(ent);
			else m_actionStep = 1;
		}

		if (m_actionStep == 1) {
			if (!m_actions[1]->m_isDone)
				m_actions[1]->tick(ent);
			else {
				unclaimTree(ent.m_wState);
				Item wood = getWoodFromTree(ent.m_wState);
				ent.m_haul = wood;
				m_actionStep = 2;
			}
		}

		if (m_actionStep == 2) {
			if (!m_actions[2]->m_isDone)
				m_actions[2]->tick(ent);
			else m_actionStep = 3;
		}

		if (m_actionStep == 3) {
			if (!m_actions[3]->m_isDone)
				m_actions[3]->tick(ent);
			else {
				m_isDone = true;
			}
		}

	}

}
//copied 1:1 from unclaimBush
void GatherWoodTreeTask::unclaimTree(const SimulationState& simState) const{

	auto treeTemp = dynamic_cast<Tree*>(simState.m_structures[m_treeIndex].get());

	treeTemp->unclaim();
}

ItemType TreeTypeToItemType(TreeType treeType){
	switch (treeType){
	case TreeType::Oak:
		return ItemType::Oak;

	case TreeType::Spruce:
		return ItemType::Spruce;

	case TreeType::Birch:
		return ItemType::Birch;

	default:
		return ItemType::Null;
	}
}

//copied 1:1 from removeFruitFromBush
Item GatherWoodTreeTask::getWoodFromTree(const SimulationState& simState) const{
	auto treeTemp = dynamic_cast<Tree*>(simState.m_structures[m_treeIndex].get());

	std::cout << "gathered " << +treeTemp->getWoodAmount() << " wood" << " from treeId: " << m_treeIndex << "\n";
	Item item = {TreeTypeToItemType(treeTemp->getTreeType()),treeTemp->getWoodAmount()};
	treeTemp->clearWoodAmount();
	return item;
}

//copied 1:1 from bush ctr
GatherWoodTreeTask::GatherWoodTreeTask(uint16_t treeIndex, SimulationState& simState): m_treeIndex(treeIndex){
	auto townHallPos = simState.m_structures[0]->m_pos;
	auto treeTemp = dynamic_cast<Tree*>(simState.m_structures[m_treeIndex].get());

	if (!treeTemp->claim()) m_isDone = false;

	m_actions.push_back(std::make_unique<MoveToAction>(uint16_t(treeTemp->m_pos.x), uint16_t(treeTemp->m_pos.y)));
	m_actions.push_back(std::make_unique<WaitAction>(treeTemp->getWoodAmount() * 10)); //gather one wood in half a second
	m_actions.push_back(std::make_unique<MoveToAction>(uint16_t(townHallPos.x),uint16_t(townHallPos.y)));
	m_actions.push_back(std::make_unique<DumpToStorageAction>());
}
