#include "storage.hpp"
#include <iostream>

std::optional<size_t> Storage::doesItemTypeExist(ItemType type) {
	for (size_t i = 0; i < m_items.size(); i++) {
		if (m_items[i].type == type) {
			return i;
		}
	}
	return std::nullopt;
}

void Storage::insertItems(Item i){
	
	auto index = doesItemTypeExist(i.type);
	if (!index) {
		m_items.push_back(i);
	}
	else {
		m_items[index.value()].count += i.count;
	}

	std::cout << "inserted "<<i.count<<" items\n";
}

bool Storage::requestItems(EntityState& ent, Item i) {

	auto index = doesItemTypeExist(i.type);
	if (!index) {
		return false;
	}
	else if (i.count > m_items[index.value()].count) return false;
	else {
		m_items[index.value()].count -= i.count; //TODO: could overflow uint64_t 

		ent.m_haul = i;
		return true;
	}

}