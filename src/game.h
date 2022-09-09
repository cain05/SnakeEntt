#pragma once

#include <entt/entt.hpp>
#include "window.h"
#include "render_system.h"
#include "move_system.h"
#include "collision_system.h"
#include "user_interface_system.h"
#include "snake_hit_self_event.h"

class Game final
{
public:
	Game();
	virtual ~Game() = default;

	void Events();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();

	void on_snake_hit_wall_event();
	void on_snake_ate_apple_event();
	void on_snake_hit_self_event(const SnakeHitSelfEvent& event);

private:

	Window window_;

	sf::Vector2i increment_;
	sf::Clock clock_;
	float elapsed_;

	entt::registry registry_;
	entt::dispatcher dispatcher_;

	RenderSystem render_system_;
	MoveSystem move_system_;
	CollisionSystem collision_system_;
	UserInterfaceSystem user_interface_system_;

	CollisionHolder collision_holder_;

	entt::entity snake_;
	int block_size_{ 16 };

	entt::entity apple_;

	int score_ { 0 };
	int lives_{ 3 };

	void ResetSnake();
	void ResetApple();
	void ExtendSnake();
	void Cut(int index);
	void Lose();
};
