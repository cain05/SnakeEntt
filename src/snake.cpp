#include "snake.h"

sf::Vector2f Snake::initial_position_ = sf::Vector2f(5.0f, 7.0f);

Snake::Snake(int block_size) :
	size_(block_size)
{
	Reset();
}

void Snake::Reset()
{
	snake_body_.clear();
	snake_body_.push_back(SnakeSegment(initial_position_.x, initial_position_.y));
	snake_body_.push_back(SnakeSegment(initial_position_.x, initial_position_.y - 1.0f));
	snake_body_.push_back(SnakeSegment(initial_position_.x, initial_position_.y - 2.0f));
}