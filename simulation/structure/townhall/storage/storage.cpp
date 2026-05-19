#include "storage.hpp"
#include <iostream>
#include "../../../../utility/logger/logger.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

std::optional<size_t> Storage::doesItemTypeExist(ItemType type) {
	for (size_t i = 0; i < m_items.size(); i++) {
		if (m_items[i].type == type) {
			return i;
		}
	}
	return std::nullopt;
}

size_t Storage::howManyItemTypeExist(ItemType type) {
	for (size_t i = 0; i < m_items.size(); i++) {
		if (m_items[i].type == type) {
			return m_items[i].count;
		}
	}
	return 0;
}

size_t Storage::howManyFromCategoryExist(ItemCategory cat) {

	size_t count = 0;

	if (cat == ItemCategory::Wood) {
	
		auto oakwood = howManyItemTypeExist(ItemType::Oak);
		auto sprucewood = howManyItemTypeExist(ItemType::Spruce);
		auto birchwood = howManyItemTypeExist(ItemType::Birch);

		count += oakwood; 
		count += sprucewood;
		count += birchwood;
		return count;
	}

	if (cat == ItemCategory::Food) {

		auto Strawberry = howManyItemTypeExist(ItemType::Strawberry);
		auto Blueberry = howManyItemTypeExist(ItemType::Blueberry);
		auto Raspberry = howManyItemTypeExist(ItemType::Raspberry);

		count += Strawberry;
		count += Blueberry;
		count += Raspberry;
		return count;
	}


	return count;
}

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

void printInsert(Item i) {
	defaultLogger.infoLog("storage +=", i.count, " ", itemTypeToString(i.type));
}

void Storage::insertItems(Item i,bool isSilent){
	
	auto index = doesItemTypeExist(i.type);
	if (!index) {
		m_items.push_back(i);
	}
	else {
		m_items[index.value()].count += i.count;
	}

	if(!isSilent)
	printInsert(i);
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

bool Storage::doesCategoryExist(ItemCategory cat) {
	
	if (cat == ItemCategory::Food) {
		auto blueberries = doesItemTypeExist(ItemType::Blueberry);
		auto strawberries= doesItemTypeExist(ItemType::Strawberry);
		auto raspberries = doesItemTypeExist(ItemType::Raspberry);

		if (blueberries || strawberries || raspberries) return true;
		else return false;
	}
	if (cat == ItemCategory::Material) {
		auto oakwood = doesItemTypeExist(ItemType::Oak);
		auto sprucewood = doesItemTypeExist(ItemType::Spruce);
		auto birchwood = doesItemTypeExist(ItemType::Birch);

		if (oakwood || sprucewood || birchwood) return true;
		else return false;
	}

	if (cat == ItemCategory::Wood) {
		auto oakwood = doesItemTypeExist(ItemType::Oak);
		auto sprucewood = doesItemTypeExist(ItemType::Spruce);
		auto birchwood = doesItemTypeExist(ItemType::Birch);

		if (oakwood || sprucewood || birchwood) return true;
		else return false;
	}

	if (cat == ItemCategory::Specific) {
		return false;
	}
	return false;
}

bool Storage::requestCategory(EntityState& ent, ItemCategory cat, uint64_t count) {
	if (cat == ItemCategory::Food) {
		auto blueberries = doesItemTypeExist(ItemType::Blueberry);
		if (blueberries.has_value()) {
			if (m_items[blueberries.value()].count > count) {
				requestItems(ent, { ItemType::Blueberry,count });
				return true;
			}
		}

		auto strawberries = doesItemTypeExist(ItemType::Strawberry);
		if (strawberries.has_value()) {
			if (m_items[strawberries.value()].count > count) {
				requestItems(ent, { ItemType::Strawberry,count });
				return true;
			}
		}

		auto raspberries = doesItemTypeExist(ItemType::Raspberry);
		if (raspberries.has_value()) {
			if (m_items[raspberries.value()].count > count) {
				requestItems(ent, { ItemType::Raspberry,count });
				return true;
			}
		}
	}

	if (cat == ItemCategory::Wood) {

		auto oak = doesItemTypeExist(ItemType::Oak);
		if (oak.has_value()) {
			if (m_items[oak.value()].count > count) {
				requestItems(ent, { ItemType::Oak,count });
				return true;
			}
		}

		auto spruce = doesItemTypeExist(ItemType::Spruce);
		if (spruce.has_value()) {
			if (m_items[spruce.value()].count > count) {
				requestItems(ent, { ItemType::Spruce,count });
				return true;
			}
		}

		auto birch = doesItemTypeExist(ItemType::Birch);
		if (birch.has_value()) {
			if (m_items[birch.value()].count > count) {
				requestItems(ent, { ItemType::Birch,count });
				return true;
			}
		}
	}

	return false;
}

void Storage::renderItemList(sf::RenderWindow& win) {
	std::string inventory = "Townhall Storage:\n";
	for (int i = 0; i < m_items.size(); i++) {
		inventory += itemTypeToString(m_items[i].type) + " " + std::to_string(m_items[i].count) + "\n";
	}
	static sf::Font font("fonts/Pixel.ttf");
	sf::Text text(font);
	text.setString(inventory);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color(255, 255, 255, 200));
	win.draw(text);
}