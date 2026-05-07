#pragma once
#include "../structure.hpp"
#include "bushtype.hpp"
#include <limits>


class Bush : public Structure {

	BushType m_BushType = BushType::Null;
	mutable bool m_isClaimed = false;
	mutable uint8_t m_fruitCount = 0;
	uint32_t m_tickCounter = 0;
public:
	bool claim() const;
	void unclaim() { m_isClaimed = false; }
	bool getClaim() const { return m_isClaimed; }
	uint8_t getFruitAmount() const { return m_fruitCount; }
	void clearFruitAmount() const { m_fruitCount = 0; }
	void render(sf::RenderWindow&) override;
	void tick() override;
	Bush(sf::Vector2f);
};