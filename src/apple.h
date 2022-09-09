#pragma once
#include <SFML/Graphics.hpp>

class Apple final
{
public:
	Apple(sf::Color color, float radius, float x, float y);
	~Apple() = default;

	sf::CircleShape circle_;
};