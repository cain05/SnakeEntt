#include "render_system.h"
#include "apple.h"
#include "snake.h"
#include "position.h"
#include "border.h"

void RenderSystem::Render(Window& window, entt::registry& registry)
{
	//render border
	//TODO

	//render borders
	auto border_view = registry.view<Border>();
	border_view.each([&](const auto& border)
	{
		window.window()->draw(border.rectangle_);
	});

	//render apple
	auto apple_view = registry.view<Apple>();
	apple_view.each([&](const auto& apple)
	{
		window.window()->draw(apple.circle_);
	});

	//render snake
	auto snake_view = registry.view<Snake>();
	snake_view.each([&](const auto& snake)
	{
		auto snake_body = snake.snake_body_;

		if (!snake_body.empty())
		{
			auto head = snake_body.begin();
			sf::RectangleShape body_part;
			body_part.setSize(sf::Vector2f(snake.size_ - 1.0f, snake.size_ - 1.0f));
			body_part.setFillColor(sf::Color::Yellow);
			body_part.setPosition(head->position_.x * snake.size_, head->position_.y * snake.size_);
			window.window()->draw(body_part);

			body_part.setFillColor(sf::Color::Green);
			for (auto itr = snake_body.begin() + 1; itr != snake_body.end(); itr++)
			{
				body_part.setPosition(itr->position_.x * snake.size_, itr->position_.y * snake.size_);
				window.window()->draw(body_part);
			}
		}
	});
}