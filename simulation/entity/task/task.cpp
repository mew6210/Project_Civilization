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
	auto bushTemp = dynamic_cast<Bush*>(simState.m_structures[m_bushIndex].get());
	
	if (!bushTemp->claim()) m_isDone = false;

	m_actions.push_back(std::make_unique<MoveToAction>(uint16_t(bushTemp->m_pos.x),uint16_t(bushTemp->m_pos.y)));
	m_actions.push_back(std::make_unique<WaitAction>(bushTemp->getFruitAmount() * 10)); //gather one fruit in half a second
}

void GatherFruitBushTask::unclaimBush(const SimulationState& simState) const {
	auto bushTemp = dynamic_cast<Bush*>(simState.m_structures[m_bushIndex].get());

	bushTemp->unclaim();
}

void GatherFruitBushTask::removeFruitsFromBush(const SimulationState& simState) const {
	auto bushTemp = dynamic_cast<Bush*>(simState.m_structures[m_bushIndex].get());

	std::cout << "gathered " << +bushTemp->getFruitAmount()<<" fruit" <<" from bushId: "<<m_bushIndex << "\n";
	bushTemp->clearFruitAmount();
	
}

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
				m_isDone = true; 
				unclaimBush(ent.m_wState);
				removeFruitsFromBush(ent.m_wState);
				//TODO: add to inventory collected fruit
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
				m_isDone = true;
				unclaimTree(ent.m_wState);
				removeWoodFromTree(ent.m_wState);
				//TODO: add to inventory collected wood
			}
		}
	}

}
//copied 1:1 from unclaimBush
void GatherWoodTreeTask::unclaimTree(const SimulationState& simState) const{

	auto treeTemp = dynamic_cast<Tree*>(simState.m_structures[m_treeIndex].get());

	treeTemp->unclaim();
}

//copied 1:1 from removeFruitFromBush
void GatherWoodTreeTask::removeWoodFromTree(const SimulationState& simState) const{
	auto treeTemp = dynamic_cast<Tree*>(simState.m_structures[m_treeIndex].get());

	std::cout << "gathered " << +treeTemp->getWoodAmount() << " wood" << " from treeId: " << m_treeIndex << "\n";
	treeTemp->clearWoodAmount();
}

//copied 1:1 from bush ctr
GatherWoodTreeTask::GatherWoodTreeTask(uint16_t treeIndex, SimulationState& simState): m_treeIndex(treeIndex){
	
	auto treeTemp = dynamic_cast<Tree*>(simState.m_structures[m_treeIndex].get());

	if (!treeTemp->claim()) m_isDone = false;

	m_actions.push_back(std::make_unique<MoveToAction>(uint16_t(treeTemp->m_pos.x), uint16_t(treeTemp->m_pos.y)));
	m_actions.push_back(std::make_unique<WaitAction>(treeTemp->getWoodAmount() * 10)); //gather one wood in half a second
}
