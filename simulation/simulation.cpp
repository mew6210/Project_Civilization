#include "simulation.hpp"
#include <iostream>

Simulation::Simulation(const MapData& md) : m_wState(md) {
	uint16_t widthHalf = m_wState.getMapSize().m_width / 2;
	uint16_t heightHalf = m_wState.getMapSize().m_height / 2;
	m_entities.push_back(Entity{ m_wState, widthHalf,heightHalf});
	m_entities.push_back(Entity{ m_wState, widthHalf,heightHalf});

}

void Simulation::simulate() {
	for (auto& ent : m_entities) {
		ent.sim();
	}
}

void Simulation::drawEntities(sf::RenderWindow& window) {
	for (const auto& ent : m_entities) {
		ent.render(window);
	}
}
