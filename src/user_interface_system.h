#pragma once
#include <SFML/Graphics.hpp>

#include "window.h"
#include "message_event.h"

using MessageContainer = std::vector<std::string>;

class UserInterfaceSystem final
{
public:

	UserInterfaceSystem();
	~UserInterfaceSystem() = default;

	void Render(Window& window);

	void on_message_event(const MessageEvent& event);
private:

	MessageContainer messages_;

	sf::RectangleShape backdrop_;
	sf::Font font_;
	sf::Text content_;
};