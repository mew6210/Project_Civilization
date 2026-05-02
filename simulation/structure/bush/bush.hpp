#include "../structure.hpp"
#include "bushtype.hpp"
#include <limits>


class Bush : public Structure {

	BushType m_BushType = BushType::Null;
	bool m_isClaimed = false;
	uint8_t m_fruitCount = 0;
	uint32_t m_tickCounter = 0;
public:
	void render(sf::RenderWindow&) override;
	void tick() override;
	Bush(sf::Vector2f);
};