#pragma once
#include "../../../item/item.hpp"
#include "../../../entity/entity.hpp"
#include <unordered_map>

class Storage {

	std::vector<Item> m_items;

	std::optional<size_t> doesItemTypeExist(ItemType);
	bool doesCategoryExist(ItemCategory);
	void insertItems(Item i);
public:
	size_t howManyFromCategoryExist(ItemCategory);
	size_t howManyItemTypeExist(ItemType type);
	void insertItems(Item, bool); //use insertItems when it should
	void operator+=(Item); // use += when insertItems should not produce a log
	bool requestItems(EntityState&, Item);
	bool requestCategory(EntityState&,ItemCategory, uint64_t);
	void renderItemList(sf::RenderWindow& win);
};