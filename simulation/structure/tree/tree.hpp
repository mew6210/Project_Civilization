#pragma once
#include "treetype.hpp"
#include "../structure.hpp"

class Tree : public Structure {

	TreeType m_TreeType = TreeType::Null;
	bool m_isClaimed = false;
	uint8_t m_woodCount = 0;
	uint32_t m_tickCounter = 0;
	uint8_t m_ticksNeededToGrow = 100;
	uint8_t m_woodLimit = 30;

public:
	bool claim();
	void unclaim();
	bool checkClaim() const;
	uint8_t getWoodAmount() const;
	TreeType getTreeType() const { return m_TreeType; }
	void clearWoodAmount();
	void render(sf::RenderWindow&) override;
	void tick() override;
	Tree(sf::Vector2f,TreeType);
	Tree(sf::Vector2f, TreeType,uint8_t,uint8_t);

	StructureType getType() const override { return StructureType::Tree; }
};