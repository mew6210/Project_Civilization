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

void Map::initMapData(const std::string& f) {
	std::ifstream file(f);
	if (!file.good()) {
		throw std::exception("map data file failed to open");
	}

	std::string line = "";
	uint16_t width = 0;
	uint16_t height = 0;
	std::vector<TileType> tiles;

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
			handleDataString(line, tiles);
		}

	}

	m_data.setWidth(width);
	m_data.setHeight(height);
	m_data.setData(tiles);
}

void Map::initMap(const std::string& file) {
	initMapData(file);
	initTexture();
}

void Map::saveMapData() {
	std::ofstream file("mapData.txt"); //TODO: should check if this file name is already taken, and suggest a different one maybe

	file << "width: " << m_data.getWidth() << "\n";
	file << "height: " << m_data.getHeight() << "\n";
	file << "data: " << m_data.getDataString() << "\n";

}

void Map::initTexture() {

	auto data = m_data.getDataCopy();
	uint64_t pixelsCount = m_data.getWidth() * m_data.getHeight();
	std::vector<uint8_t> pixels(pixelsCount * 4);
	
	for (size_t i = 0; i < data.size(); ++i) {

		sf::Color color;

		switch (data[i]) {
			case TileType::TreeSoil: color = sf::Color(22, 102, 46); break;
			case TileType::FertileSoil: color = sf::Color(30, 235, 92); break;
			case TileType::SemiFertileSoil: color = sf::Color(163, 224, 92); break;
			case TileType::NotFertileSoil: color = sf::Color(135, 126, 82); break;
		}

		pixels[i * 4 + 0] = color.r;
		pixels[i * 4 + 1] = color.g;
		pixels[i * 4 + 2] = color.b;
		pixels[i * 4 + 3] = color.a;

	}

	if (!(m_texture.resize({ m_data.getWidth(), m_data.getHeight() }))) {
		throw std::exception("error resizing texture");
	}

	m_texture.update(pixels.data());
}