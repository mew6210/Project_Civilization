#pragma once
#include "../structure.hpp"
#include "bushtype.hpp"

class Bush : public Structure {

	BushType m_BushType = BushType::Null;
	bool m_isClaimed = false;
	uint8_t m_fruitCount = 0;
	uint8_t m_ticksNeededToGrow = 100;
	uint8_t m_fruitLimit = 30;
	uint32_t m_tickCounter = 0;
public:
	bool claim();
	void unclaim() { m_isClaimed = false; }
	bool checkClaim() const { return m_isClaimed; }
	uint8_t getFruitAmount() const { return m_fruitCount; }
	BushType getBushType() const { return m_BushType; }
	void clearFruitAmount() { m_fruitCount = 0; }
	void render(sf::RenderWindow&) override;
	void tick() override;
	Bush(sf::Vector2f pos, BushType bushType, uint8_t ticksToGrow, uint8_t fruitLimit);
	Bush(sf::Vector2f,BushType);
	StructureType getType() const override { return StructureType::Bush; }
};