#include "../structure.hpp"

class House : public Structure {

	std::vector<uint16_t> m_visitorsIds;
	bool m_isClaimed = false;

	void render(sf::RenderWindow&) override;
	void tick() override;

public:
	House(sf::Vector2f);
	uint16_t getVisitorsAmount() const { return (uint16_t)m_visitorsIds.size(); }
	void checkIn(uint16_t id);
	void checkOut(uint16_t id);
	StructureType getType() const override { return StructureType::House; }
};