#include "border.h"

Border::Border(float x, float y, float width, float height)
{
	rectangle_.setSize({ width, height });
	rectangle_.setPosition(x, y);
	rectangle_.setFillColor(sf::Color(150, 0, 0));
}