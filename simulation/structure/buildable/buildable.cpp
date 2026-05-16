#include "buildable.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace {
	constexpr sf::Color k_BuildingColor = sf::Color(94, 70, 19);
}

void Buildable::handleStorageInitialization(BuildableType type) {
	if (type == BuildableType::House) {
		m_recipe.addNeed(ItemCategory::Wood, 10);
	}
	else if (type == BuildableType::Farm) {
		m_recipe.addNeed(ItemCategory::Food, 10);
	}
	else if (type == BuildableType::Quarry) {
		m_recipe.addNeed(ItemCategory::Wood, 50);
	}
}

Buildable::Buildable(BuildableType type, sf::Vector2f pos): Structure(pos),m_type(type) {
	handleStorageInitialization(type);
}

std::vector<ItemCategory> Buildable::getNeededItems() {
	
	std::vector<ItemCategory> neededCategories;

	for (auto& matNeeded : m_recipe.m_materialsNeeded) {

		if (m_storage.howManyFromCategoryExist(matNeeded.first) > matNeeded.second) {
			neededCategories.push_back(matNeeded.first);
		}

	}

	return neededCategories;
}

void Buildable::insertMaterials(EntityState& ent) {

	m_storage.insertItems(ent.m_haul,true);
	ent.m_haul = {};

}

void Buildable::tick() {
	
	if (m_tickCounter % 100 == 0) {
		auto vec = getNeededItems();
		if (vec.size() == 0) m_isBuilt = true;
	}

	m_tickCounter++;
}

/*
	Currently renders a 1x1 buildable as a 4x4 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void Buildable::render(sf::RenderWindow& win) {

	sf::RectangleShape shape{ sf::Vector2f{4,4} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(m_pos);
	shape.setFillColor(k_BuildingColor);

	win.draw(shape);
}