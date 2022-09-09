#pragma once

#include "velocity.h"

#include "key_pressed_event.h"

class MoveSystem final
{
public:
	MoveSystem() = default;
	~MoveSystem() = default;

	void on_key_pressed_event(const KeyPressedEvent& key_down) noexcept;

	void Update(entt::registry& registry);

	void on_snake_hit_wall_event() noexcept;

private:
	Direction new_snake_direction_ { Direction::None };
	Direction current_snake_direction_{ Direction::None };
};