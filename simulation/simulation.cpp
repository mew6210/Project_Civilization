#include "simulation.hpp"
#include <iostream>

Simulation::Simulation(const MapData& md) : m_wState(md) {

	m_entities.push_back(Entity{ m_wState, 100,100});
	m_entities.push_back(Entity{ m_wState, 200,200});
	m_entities.push_back(Entity{ m_wState, 300,300});
	m_entities.push_back(Entity{ m_wState, 400,400});
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
