#pragma once

struct KeyPressedEvent final
{
	inline KeyPressedEvent(sf::Keyboard::Key key)
		: key_(key)
	{
	}

	sf::Keyboard::Key key_;
};