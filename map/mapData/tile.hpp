#pragma once

enum class TileType : uint8_t {
	Water,  //0
	TreeSoil, //1
	FertileSoil, //2
	SemiFertileSoil, //3
	NotFertileSoil //4
};
//in map file, they are addressed as if they would be an int, exactly like shown above