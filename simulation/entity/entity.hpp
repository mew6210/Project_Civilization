#include <cstdint>
#include "../worldstate/worldstate.hpp"
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Task;
class Action;

struct Entity {
	uint32_t m_id = 0;
	uint16_t m_posX = 0;
	uint16_t m_posY = 0;

	std::vector<std::unique_ptr<Task>> m_tasks = {};
	uint16_t m_curTask = 0;

	const WorldState& m_wState;

	Entity(const WorldState& wState) : m_wState(wState) {}
	Entity(const WorldState& wState, uint16_t posX, uint16_t posY) :m_posX(posX), m_posY(posY), m_wState(wState) {}
	void render(sf::RenderWindow& window) const;
	void sim();
};

struct Task {
	Entity& m_ent; //TODO: REFACTOR TO ENTITY_STATE
	std::vector<std::unique_ptr<Action>> m_actions;
	uint8_t m_actionStep = 0;
	virtual void tick() = 0;
	Task(Entity& e) :m_ent(e) {}
};

class WanderRandTask : public Task {
	using Task::Task; //copies a constructor from task
	uint8_t m_tickCounter = 0;
	void tick() override;
};

struct Action {
	Entity& m_ent; //TODO: REFACTOR TO ENTITY_STATE
	bool m_isDone = false;

	virtual void tick() = 0;
public:
	Action(Entity& e) :m_ent(e) {}
};

struct MoveToAction : public Action {
	uint16_t m_DestinationX;
	uint16_t m_DestinationY;

	MoveToAction(Entity& e,uint16_t destinationX,uint16_t destinationY):
		Action(e),
		m_DestinationX(destinationX),
		m_DestinationY(destinationY){}
	void tick() override;
};