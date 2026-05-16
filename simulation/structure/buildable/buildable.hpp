#include "../structure.hpp"
#include "../../structure/townhall/storage/storage.hpp"
#include "recipe/recipe.hpp"
#include <vector>

enum class BuildableType {
	House,
	Farm,
	Quarry
};

class Buildable : public Structure {

	Recipe m_recipe;
	Storage m_storage = {};
	bool m_isBuilt = false;
	BuildableType m_type = {};
	uint64_t m_tickCounter = 0;

	void handleStorageInitialization(BuildableType);

public:
	void render(sf::RenderWindow&);
	void tick();
	void insertMaterials(EntityState&);
	std::vector<ItemCategory> getNeededItems();
	BuildableType getBuildingType() const { return m_type; }
	Buildable(BuildableType, sf::Vector2f);
};