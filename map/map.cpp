#include "map.hpp"
#include <fstream>
#include <iostream>

namespace trimLib{

	const std::string whiteSpaces(" \f\n\r\t\v");


	void trimRight(std::string& str,
		const std::string& trimChars = whiteSpaces)
	{
		std::string::size_type pos = str.find_last_not_of(trimChars);
		str.erase(pos + 1);
	}


	void trimLeft(std::string& str,
		const std::string& trimChars = whiteSpaces)
	{
		std::string::size_type pos = str.find_first_not_of(trimChars);
		str.erase(0, pos);
	}


	void trim(std::string& str, const std::string& trimChars = whiteSpaces)
	{
		trimRight(str, trimChars);
		trimLeft(str, trimChars);
	}
}

void handleDataString(const std::string& line,std::vector<TileType>& data) {

	std::string buf = "";
	for (size_t i = 0; i < line.size(); i++) {

		if (line[i] != ' ') buf.push_back(line[i]);
		if (line[i] == ' '|| i == line.size()-1) { //if its space between next number or end of file
			data.push_back(static_cast<TileType>(std::stoi(buf))); //interpret buffer as a TileType, and add it to data vector
			buf.clear();
		}
	}

}

void Map::loadMapData(const std::string& f) {

	std::ifstream file(f);
	if (!file.good()) {
		throw std::exception("map data file failed to open");
	}

	std::string line = "";
	uint16_t width = 0;
	uint16_t height = 0;
	std::vector<TileType> data;

	while (std::getline(file, line)) {
		if (line.size() == 0) continue;
		if (line.starts_with('#')) continue; //treat # as a comment
		if (line.starts_with("width:")) {
			std::string widthStr = line.substr(6);
			width = std::stoi(widthStr);
		}
		if (line.starts_with("height:")) {
			std::string heightStr = line.substr(7);
			height = std::stoi(heightStr);
		}
		if (line.starts_with("data: ")) {
			line = line.substr(5);
			trimLib::trim(line);
			handleDataString(line, data);
		}

	}

	m_mapData.setWidth(width);
	m_mapData.setHeight(height);
	m_mapData.setData(data);
}

void Map::saveMapData() {
	std::ofstream file("mapData.txt"); //TODO: should check if this file name is already taken, and suggest a different one maybe

	file << "width: " << m_mapData.getWidth() << "\n";
	file << "height: " << m_mapData.getHeight() << "\n";
	file << "data: " << m_mapData.getDataString() << "\n";

}