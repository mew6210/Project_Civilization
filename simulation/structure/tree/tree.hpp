#include "treetype.hpp"
#include "../structure.hpp"

class Tree : public Structure {

	TreeType m_TreeType = TreeType::Null;
	bool m_isClaimed = false;
	uint8_t m_woodCount= 0;
	uint32_t m_tickCounter = 0;
public:
	void render(sf::RenderWindow&) override;
	void tick() override;
	Tree(sf::Vector2f);
};