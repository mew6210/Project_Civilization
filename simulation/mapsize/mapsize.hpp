#include <cstdint>
#pragma once

/*
	POD container for dimensions of a map
*/
struct MapSize {
	uint16_t m_width = 0;
	uint16_t m_height = 0;
};