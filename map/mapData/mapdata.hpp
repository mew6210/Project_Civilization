#pragma once
#include <cstdint>
#include "tile.hpp"
#include <vector>
#include <string>

/*
	@brief Holds size and pixels of a map.

	You probably should not initialize it outside of Map or Simulation class.

*/
class MapData {

	uint16_t m_width = 0;
	uint16_t m_height = 0;
	std::vector<TileType> m_data = {};

	std::string dataToDataString() const;

public:
	TileType getTile(const uint16_t& row, const uint16_t& col);
	void setWidth(const uint16_t& w) { m_width = w; }
	void setHeight(const uint16_t& h) { m_height = h; }
	void setData(std::vector<TileType>& d) { m_data = std::move(d); }
	uint16_t getWidth() const { return m_width; }
	uint16_t getHeight() const { return m_height; }
	std::string getDataString() const { return dataToDataString(); };
	std::vector<TileType> getDataCopy() { return m_data; }
};