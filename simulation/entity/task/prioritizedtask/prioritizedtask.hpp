#include "../task.hpp"

struct PrioritizedTask {
	std::unique_ptr<Task> task;
	uint8_t priority;
};