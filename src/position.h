#pragma once

class Position final
{
public:
	Position(float x, float y);
	~Position() = default;

	float x_;
	float y_;
};