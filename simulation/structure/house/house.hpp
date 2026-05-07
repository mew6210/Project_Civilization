#include "../structure.hpp"

class House : public Structure {

	uint32_t m_ownerId = 0; //id of an entity
	bool m_isClaimed = false;

	void render(sf::RenderWindow&) override;
	void tick() override;

	House(sf::Vector2f);
	StructureType getType() const override { return StructureType::House; }
};