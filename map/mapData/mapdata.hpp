#pragma once
#include <cstdint>
#include "tile.hpp"
#include <vector>

class MapData {

	uint16_t m_width = 0;
	uint16_t m_height = 0;
	std::vector<TileType> m_data = {};

public:
	void setWidth(const uint16_t& w) { m_width = w; }
	void setHeight(const uint16_t& h) { m_height = h; }
	void setData(std::vector<TileType>& d) { m_data = std::move(d); }
};