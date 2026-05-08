#include "../../../item/item.hpp"
#include "../../../entity/entity.hpp"
#include <unordered_map>

class Storage {

	std::vector<Item> m_items;

	std::optional<size_t> doesItemTypeExist(ItemType);
public:
	void insertItems(Item);
	bool requestItems(EntityState&, Item);
};