#include "../../../item/item.hpp"
#include <vector>

struct Recipe {

	std::vector<std::pair<ItemCategory, uint64_t>> m_materialsNeeded;

	void addNeed(ItemCategory, uint64_t);
};
