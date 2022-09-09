#include "SFML/Window/Event.hpp"
#include "entt/entt.hpp"
#include "snake.h"
#include "move_system.h"

void MoveSystem::on_key_pressed_event(const KeyPressedEvent& key_down) noexcept
{
	switch (key_down.key_)
	{
		case sf::Keyboard::Up:
			new_snake_direction_ = Direction::Up;
			break;
		case sf::Keyboard::Down:
			new_snake_direction_ = Direction::Down;
			break;
		case sf::Keyboard::Left:
			new_snake_direction_ = Direction::Left;
			break;
		case sf::Keyboard::Right:
			new_snake_direction_ = Direction::Right;
			break;
	}
}

void MoveSystem::Update(entt::registry& registry)
{
	auto snake_view = registry.view<Snake>();
	snake_view.each([&](auto& snake)
	{
			auto physical_direction = Direction::None;

			//physical direction
			if (snake.snake_body_.size() > 2)
			{
				if (snake.snake_body_[0].position_.x == snake.snake_body_[1].position_.x)
				{
					physical_direction = (snake.snake_body_[0].position_.y > snake.snake_body_[1].position_.y
						? Direction::Down : Direction::Up);
				}
				else if (snake.snake_body_[0].position_.y == snake.snake_body_[1].position_.y)
				{
					physical_direction = (snake.snake_body_[0].position_.x > snake.snake_body_[1].position_.x
						? Direction::Right : Direction::Left);
				}
			}

			//now set direction
			if (new_snake_direction_ == Direction::Up && physical_direction != Direction::Down)
			{
				current_snake_direction_ = Direction::Up;
			}
			else if (new_snake_direction_ == Direction::Down && physical_direction != Direction::Up)
			{
				current_snake_direction_ = Direction::Down;
			}
			else if (new_snake_direction_ == Direction::Left && physical_direction != Direction::Right)
			{
				current_snake_direction_ = Direction::Left;
			}
			else if (new_snake_direction_ == Direction::Right && physical_direction != Direction::Left)
			{
				current_snake_direction_ = Direction::Right;
			}

			//finally move snake
			if (current_snake_direction_ != Direction::None)
			{
				for (auto i = snake.snake_body_.size() - 1; i > 0; --i) {
					snake.snake_body_[i].position_ = snake.snake_body_[i - 1].position_;
				}
				if (current_snake_direction_ == Direction::Left) {
					snake.snake_body_[0].position_.x = snake.snake_body_[0].position_.x - 1;
				}
				else if (current_snake_direction_ == Direction::Right) {
					++snake.snake_body_[0].position_.x;
				}
				else if (current_snake_direction_ == Direction::Up) {
					--snake.snake_body_[0].position_.y;
				}
				else if (current_snake_direction_ == Direction::Down) {
					++snake.snake_body_[0].position_.y;
				}
			}
	});
}

void MoveSystem::on_snake_hit_wall_event() noexcept
{
	new_snake_direction_ = Direction::None;
	current_snake_direction_ = Direction::None;
}