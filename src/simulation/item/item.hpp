#pragma once
#include "itemtype.hpp"
#include <cstdint>

struct Item {
	ItemType type = ItemType::Null;
	uint64_t count = 0;
};