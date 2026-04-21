#include "mapdata.hpp"

std::string MapData::dataToDataString() const {

	std::string buf = "";

	for (size_t i = 0; i < m_data.size(); i++) {
		auto tile = static_cast<uint8_t>(m_data[i]);
		
		char c = tile + '0';
		buf.push_back(c);
		buf.push_back(' ');
	}
	return buf;
}

TileType MapData::getTile(const uint16_t& row, const uint16_t& col) {
	return m_data[row * m_width + col];
}