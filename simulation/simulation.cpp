#include "simulation.hpp"
#include "entity/entity.hpp"
#include <iostream>

Simulation::Simulation(const MapData& md) : m_wState(md) {
	m_wState.m_entities.reserve(1000);
	uint16_t widthHalf = m_wState.getMapSize().m_width / 2;
	uint16_t heightHalf = m_wState.getMapSize().m_height / 2;
	m_wState.m_entities.push_back(Entity{ m_wState, widthHalf,heightHalf });
	m_wState.m_entities.push_back(Entity{ m_wState, widthHalf,heightHalf });

}

void Simulation::simulate() {
	for (auto& ent : m_wState.m_entities) {
		ent.sim();
	}
	for (auto& structure : m_wState.m_structures) {
		structure->tick();
	}
}

void Simulation::renderEntities(sf::RenderWindow& window) {
	for (const auto& ent : m_wState.m_entities) {
		ent.render(window);
	}
}

void Simulation::spawnAt(sf::Vector2f pos, ActiveTool type) {
	if (type == ActiveTool::None)   return;
	if (type == ActiveTool::Bush)   m_wState.addStructure(pos, StructureType::Bush);
	if (type == ActiveTool::Tree)   m_wState.addStructure(pos, StructureType::Tree);
	if (type == ActiveTool::Entity) m_wState.m_entities.push_back(Entity{ m_wState, (uint16_t)pos.x, (uint16_t)pos.y });
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