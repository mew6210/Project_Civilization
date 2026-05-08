#include "../structure.hpp"
#include "../../simulationstate/simulationstate.hpp"

class TownHall : public Structure {

	uint64_t tickCounter = 1;

	SimulationState& m_simState;
	//Inventory inv = {};


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

public:
	void render(sf::RenderWindow&) override;
	void tick() override;
	TownHall(sf::Vector2f, SimulationState&);
	StructureType getType() const override { return StructureType::TownHall; }
};