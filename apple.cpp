#include "apple.h"

Apple::Apple(sf::Color color, float radius, float x, float y)
{
	circle_.setFillColor(color);
	circle_.setRadius(radius);
	circle_.setPosition(x, y);
}