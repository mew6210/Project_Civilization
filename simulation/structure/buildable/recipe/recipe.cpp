#include "recipe.hpp"

void Recipe::addNeed(ItemCategory cat, uint64_t count) {
	m_materialsNeeded.push_back({ cat,count });
}