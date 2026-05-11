#pragma once
#include <SFML/Graphics/Texture.hpp>

sf::Vector2f randomGradient(int ix, int iy, unsigned int seed);
float dotProduct(int ix, int iy, float x, float y, unsigned int seed);
float interpolation(float a0, float a1, float w);
float perlin(float x, float y, unsigned int seed);
void generateMap(std::string name,unsigned int seed);