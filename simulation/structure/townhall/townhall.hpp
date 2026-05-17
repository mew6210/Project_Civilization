#include "../structure.hpp"
#include "../../simulationstate/simulationstate.hpp"
#include "storage/storage.hpp"

class TownHall : public Structure {

	uint64_t tickCounter = 1;

	SimulationState& m_simState;


	//bush-related
	std::optional<uint16_t> findBushToGather(uint8_t);
	void delegateGatherBushTask();
	bool isSuitableBush(uint8_t, uint8_t, Bush*) const;

	//entity-related
	std::optional<uint16_t> findNotBusyEntityId();
	uint16_t getEntityVectorIndexByEntityId(uint16_t);

	//tree-related
	void delegateGatherWoodTreeTask();
	std::optional<uint16_t> findTreeToGather(uint8_t);
	bool isSuitableTree(uint8_t, uint8_t,Tree*) const;

	//building-related
	void handleBuildings();
	void queueBuildings();
	sf::Vector2f getSuitableHousePosition();
	void delegateBuildBuildingsTask();
	std::optional<std::pair<uint16_t, ItemCategory>> findBuildingToBuild();
	std::vector<std::pair<size_t, std::vector<ItemCategory>>> getBuildingsAndNeeds();
	std::vector<ItemCategory> getCurrentTownHallMaterialsAvailable();
	uint16_t countBuiltHouses();

	//mating-related
	std::optional<std::pair<uint16_t,uint16_t>> findSuitablePair();
	uint16_t findNotBusyHouse();
	void delegateMatingTask();

	void addStartingItems();
public:

	std::vector<std::unique_ptr<Structure>> m_buildingQueue = {};
	uint8_t m_BuildingsScheduled = 0;
	Storage inv = {};

	void render(sf::RenderWindow&) override;
	void tick() override;
	TownHall(sf::Vector2f, SimulationState&);
	StructureType getType() const override { return StructureType::TownHall; }
};