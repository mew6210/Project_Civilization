#include "../structure.hpp"

class House : public Structure {

	uint32_t m_ownerId = 0;
	bool m_isClaimed = false;

	void render(sf::RenderWindow&) override;
	void tick() override;

	House(sf::Vector2f);
};