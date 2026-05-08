#include "tree.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace {

	constexpr uint8_t k_TicksNeededToGrow = 100;
	constexpr uint8_t k_WoodLimit = std::numeric_limits<uint8_t>::max();
	constexpr sf::Color k_TreeColor = sf::Color(115, 81, 37);
}

/*
	Currently renders a 1x1 tree as a 4x4 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void Tree::render(sf::RenderWindow& win) {

	sf::RectangleShape shape{ sf::Vector2f{4,4} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(m_pos);
	shape.setFillColor(k_TreeColor);

	win.draw(shape);
}

void Tree::tick() {
	if (m_tickCounter % k_TicksNeededToGrow == 0) {
		if (m_woodCount < k_WoodLimit) {
			++m_woodCount;
		}
	}

	m_tickCounter++;
}

Tree::Tree(sf::Vector2f pos,TreeType treeType) : Structure(pos),m_TreeType(treeType) {}

bool Tree::claim() {
	
	if (m_isClaimed) return false;
	else {
		m_isClaimed = true;
		return true;
	}

}

void Tree::unclaim() { m_isClaimed = false; }
bool Tree::checkClaim() const { return m_isClaimed; }
uint8_t Tree::getWoodAmount() const { return m_woodCount; }
void Tree::clearWoodAmount() { m_woodCount = 0; }