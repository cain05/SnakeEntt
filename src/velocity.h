#pragma once

enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};

class Velocity final
{

public:
	Velocity(float speed, Direction direction);
	~Velocity() = default;

	float speed_;
	Direction direction_;
};
