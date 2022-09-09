#pragma once

struct SnakeHitSelfEvent final
{
	SnakeHitSelfEvent(int cut_index) : cut_index_(cut_index)
	{

	}
	int cut_index_;
};