#pragma once

#include <entt/entt.hpp>

struct CollisionHolder
{
	entt::entity snake;
	entt::entity apple;

	int grid_size_x;
	int grid_size_y;

	entt::registry* registry;
};

class CollisionSystem final
{
public:
	CollisionSystem() = default;
	~CollisionSystem() = default;

	void Update(CollisionHolder& collision_holder, entt::dispatcher& dispatcher);
};