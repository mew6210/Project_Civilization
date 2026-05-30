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
	bool m_isClaimed = false;
	BuildableType m_type = {};
	uint64_t m_tickCounter = 0;

	void handleStorageInitialization(BuildableType);

public:
	void claim() { m_isClaimed = true; }//should return bool if fails, but whatever
	bool checkisBuilt() { return m_isBuilt; }
	bool isClaimed() { return m_isClaimed; }
	void unclaim() { m_isClaimed = false; }
	void render(sf::RenderWindow&) override;
	void tick() override;
	void insertMaterials(EntityState&);
	std::vector<ItemCategory> getNeededItems();
	StructureType getType() const { return StructureType::Building; };
	BuildableType getBuildingType() const { return m_type; }
	Buildable(BuildableType, sf::Vector2f);
};