#include "collision_system.h"
#include "apple.h"
#include "border.h"
#include "snake.h"
#include "position.h"

#include "snake_hit_wall_event.h"
#include "snake_ate_apple_event.h"
#include "snake_hit_self_event.h"

void CollisionSystem::Update(CollisionHolder& collision_holder, entt::dispatcher& dispatcher)
{
	const auto apple_position = collision_holder.registry->try_get<Position>(collision_holder.apple);
	const auto snake = collision_holder.registry->try_get<Snake>(collision_holder.snake);

	if (snake != nullptr && apple_position != nullptr)
	{
		if (snake->snake_body_[0].position_ == sf::Vector2f(apple_position->x_, apple_position->y_))
		{
			dispatcher.trigger<SnakeAteAppleEvent>();
		}

		if (snake->snake_body_[0].position_.x <= 0 ||
			snake->snake_body_[0].position_.y <= 0 ||
			snake->snake_body_[0].position_.x >= collision_holder.grid_size_x - 1 ||
			snake->snake_body_[0].position_.y >= collision_holder.grid_size_y - 1)
		{
			dispatcher.trigger<SnakeHitWallEvent>();
		}

		if (snake->snake_body_.size() > 4)
		{
			SnakeSegment& head = snake->snake_body_.front();
			for (int i = 1; i < snake->snake_body_.size(); i++) {
				if (snake->snake_body_[i].position_ == snake->snake_body_[0].position_)
				{
					dispatcher.trigger<SnakeHitSelfEvent>(SnakeHitSelfEvent(i));
					break;
				}
			}
			for (auto itr = snake->snake_body_.begin() + 1; itr != snake->snake_body_.end(); ++itr)
			{
				if (itr->position_ == head.position_) {
					
					break;
				}
			}
		}
	}
}