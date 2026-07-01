#include "itemtypetostring.hpp"

std::string itemTypeToString(ItemType t) {
	switch (t) {
	case ItemType::Strawberry: return "Strawberry";
	case ItemType::Blueberry: return "Blueberry";
	case ItemType::Raspberry: return "Raspberry";
	case ItemType::Oak: return "Oak";
	case ItemType::Spruce: return "Spruce";
	case ItemType::Birch: return "Birch";
	case ItemType::Null: return "Null";
	default: return "should NEVER happen";
	}
}
