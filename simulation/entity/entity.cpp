#include "entity.hpp"
#include <algorithm>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#include "../simulationstate/simulationstate.hpp"

namespace {
	constexpr int k_HungerTickDecreaseCount = 20;
	constexpr int k_HealthTickDecreaseFromHungerCount = 20;
	constexpr int k_HealthTickIncreaseFromSatiationCount = 10;
	constexpr int k_GoEatTaskPriority = 5;
	constexpr int k_GoEatTaskCooldownTicks = 100;
	constexpr int k_GoEatTaskSatiationLimit = 30;
	constexpr int k_AgingTickCount = 200;
	constexpr int k_EvaluateDeathTickCount = 100;
	constexpr int k_MatingCd = 500;
}

/*
	Currently renders a 1x1 entity based on a type as a 4x4 square

	TODO: maybe should be changed later to 1x1, when zoom is implemented
*/
void Entity::render(sf::RenderWindow& window) const {
	sf::RectangleShape shape{ sf::Vector2f{4,4} }; //shape created every frame, TODO: make it static or something like that
	shape.setPosition(sf::Vector2f{ float(m_entState.m_posX),float(m_entState.m_posY) });
	shape.setFillColor(sf::Color::Red);

	window.draw(shape);
}

void Entity::doCurrentTask() {
	if (!m_tasks[0].task->m_isDone) {
		m_tasks[0].task->tick(m_entState);
	}
	else m_tasks.pop_back();
}

bool Entity::isHungry() {
	return (
		m_tickCounter % k_HungerTickDecreaseCount == 0 &&
		m_entState.m_satiation != 0);
}

bool Entity::isStarving(){
	return (m_entState.m_satiation == 0 &&
		m_entState.m_health != 0 &&
		m_tickCounter % k_HealthTickDecreaseFromHungerCount == 0);
}

bool Entity::isFull(){
	return (m_entState.m_satiation > k_GoEatTaskSatiationLimit &&
		m_entState.m_health != 100 &&
		m_tickCounter % k_HealthTickIncreaseFromSatiationCount == 0);
}

void Entity::handleIsAcceptingTasks() {
	if (m_entState.m_satiation < k_GoEatTaskSatiationLimit) m_isAcceptingTasks = false;
	if (m_entState.m_satiation > k_GoEatTaskSatiationLimit) m_isAcceptingTasks = true;
}

//AI GENERATED
void Entity::evalDeath() {

	if (m_entState.m_age < 70) return;

	const int N = 10000;

	float age = (float)m_entState.m_age;

	float k = 0.001f; // tuning parameter (very important)

	float p = 1.0f - expf(-age * k);

	int threshold = (int)(p * N);

	int roll = m_entState.m_wState.getRandInt(0,N-1);

	if (roll < threshold)
	{
		m_entState.m_isDead = true;
		m_entState.m_naturalCauses = true;
	}

}

void Entity::updateStats() {

	if (m_tickCounter % k_AgingTickCount == 0) m_entState.m_age++;
	if (m_tickCounter % k_EvaluateDeathTickCount == 0) evalDeath();
	if (isHungry()) m_entState.m_satiation--;
	if (isStarving()) m_entState.m_health--;
	if (isFull()) m_entState.m_health++;	
	handleIsAcceptingTasks();
	if (m_entState.m_health == 0) m_entState.m_isDead = true;

	m_tickCounter++;
	if (m_entState.m_matingCd != 0) m_entState.m_matingCd--;
}

void Entity::addHungryTask() {
	auto tsk = PrioritizedTask{
			std::make_unique<GetFoodAndEatTask>(m_entState.m_wState),
			k_GoEatTaskPriority
	};
	delegateTask(std::move(tsk),true);
}

void Entity::addTasksWhenNone() {
	if (m_entState.m_satiation < k_GoEatTaskSatiationLimit &&
		m_tickCounter % k_GoEatTaskCooldownTicks == 0
		)
	{
		addHungryTask();

	}
}

void Entity::addTasksWhenSome() {

	if (m_entState.m_satiation < k_GoEatTaskSatiationLimit &&
		m_tasks[0].priority != k_GoEatTaskPriority
		&& m_tickCounter % k_GoEatTaskCooldownTicks == 0
		) {
		addHungryTask();
	}
}

//adds tasks needed by the entity
void Entity::addTasks() {
	if (m_tasks.size() == 0) {
		addTasksWhenNone();
	}
	else {
		addTasksWhenSome();
	}

}

void Entity::sim() {
		
	if (m_tasks.empty()) m_tasks.push_back({std::make_unique<WanderRandTask>(),0});
	
	doCurrentTask();
	updateStats();
	addTasks();
}

void Entity::delegateTask(PrioritizedTask tsk, bool force) const {

	if (!m_isAcceptingTasks && !force) return;

	if (m_tasks.size() == 1) {
		if (m_tasks[0].priority == 0) {
			m_tasks.erase(m_tasks.begin());
		}
	}

	m_tasks.push_back(std::move(tsk));

	std::sort(m_tasks.begin(), m_tasks.end(), [](const PrioritizedTask& a, const PrioritizedTask& b) {
		return a.priority > b.priority;
		});
}
