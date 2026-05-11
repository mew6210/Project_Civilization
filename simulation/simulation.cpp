#include "simulation.hpp"
#include "entity/entity.hpp"
#include <iostream>
#include "../utility/logger.hpp"

Simulation::Simulation(const MapData& md) : m_wState(md) {
	m_wState.m_entities.reserve(1000);
	uint16_t widthHalf = m_wState.getMapSize().m_width / 2;
	uint16_t heightHalf = m_wState.getMapSize().m_height / 2;
	m_wState.m_entities.push_back(std::make_unique<Entity>( m_wState, widthHalf,heightHalf));
	m_wState.m_entities.push_back(std::make_unique<Entity>( m_wState, widthHalf,heightHalf));
	m_wState.addStructure({ float(widthHalf),float(heightHalf)}, StructureType::TownHall);

}

void Simulation::simulateEntities() {

	for (auto it = m_wState.m_entities.begin();
		it != m_wState.m_entities.end(); ) {

		if ((*it)->m_entState.m_isDead) {
			defaultLogger.warningLog("entity died, id: ", (*it)->m_entState.m_id);
			it = m_wState.m_entities.erase(it);
		}
			
		else {
			(*it)->sim();
			++it;
		}
	}

}
void Simulation::simulateStructures(){
	for (auto& structure : m_wState.m_structures) {
		structure->tick();
	}
}

void Simulation::simulate() {
	simulateEntities();
	simulateStructures();
}

void Simulation::renderEntities(sf::RenderWindow& window) {
	for (const auto& ent : m_wState.m_entities) {
		ent->render(window);
	}
}

void Simulation::spawnAt(sf::Vector2f pos, ActiveTool type) {
	if (type == ActiveTool::None)   return;
	if (type == ActiveTool::Bush)   m_wState.addStructure(pos, StructureType::Bush);
	if (type == ActiveTool::Tree)   m_wState.addStructure(pos, StructureType::Tree);
	if (type == ActiveTool::Entity) m_wState.m_entities.push_back(std::make_unique<Entity>( m_wState, (uint16_t)pos.x, (uint16_t)pos.y ));
}

void Simulation::renderStructures(sf::RenderWindow& window) {
	for (const auto& structure : m_wState.m_structures) {
		structure->render(window);
	}
}

void Simulation::render(sf::RenderWindow& window) {
	renderEntities(window);
	renderStructures(window);
}