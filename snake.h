#pragma once

#include <SFML/Graphics.hpp>

struct SnakeSegment
{
	SnakeSegment(float x, float y) :
		position_(x, y)
	{
	}

	sf::Vector2f position_;
};

using SnakeContainer = std::vector<SnakeSegment>;

class Snake final
{
public:
	Snake(int size);
	~Snake() = default;

	static sf::Vector2f initial_position_;

	SnakeContainer snake_body_;
	sf::RectangleShape body_rectangle_;
	int size_;

	void Reset();

private:
		
	int lives_;
	
};