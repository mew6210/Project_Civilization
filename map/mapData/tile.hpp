#pragma once

enum class TileType : uint8_t {
	TreeSoil = 0, //0
	FertileSoil, //1
	SemiFertileSoil, //2
	NotFertileSoil //3
};
//in map file, they are addressed as if they would be an int, exactly like shown above