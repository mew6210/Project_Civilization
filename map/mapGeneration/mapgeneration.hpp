#pragma once
#include <SFML/Graphics/Texture.hpp>

sf::Vector2f randomGradient(int, int, unsigned int);
float dotProduct(int, int, float, float, unsigned int);
float interpolation(float, float, float);
float perlin(float, float, unsigned int);
void generateMap(std::string, int, int);