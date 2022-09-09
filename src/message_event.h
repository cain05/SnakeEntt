#pragma once
#include <string>

struct MessageEvent final
{
	inline MessageEvent(std::string& message) :
		message_(message)
	{

	}

	std::string message_;
};
