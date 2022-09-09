#pragma once

#include <SFML/Graphics.hpp>

class Border final
{
public:
	Border(float x, float y, float width, float height);
	~Border() = default;

	sf::RectangleShape rectangle_;
};