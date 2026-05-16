#include "../../../item/item.hpp"
#include "../../../entity/entity.hpp"
#include <unordered_map>

class Storage {

	std::vector<Item> m_items;

	std::optional<size_t> doesItemTypeExist(ItemType);
	bool doesCategoryExist(ItemCategory);
public:
	size_t howManyFromCategoryExist(ItemCategory);
	void insertItems(Item,bool);
	bool requestItems(EntityState&, Item);
	bool requestCategory(EntityState&,ItemCategory, uint64_t);
};