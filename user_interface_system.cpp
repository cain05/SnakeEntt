#include "user_interface_system.h"

UserInterfaceSystem::UserInterfaceSystem()
{
	sf::Vector2f offset(2.0f, 2.0f);
	sf::Vector2f screen_position(255, 0);
	int character_size = 14;

	font_.loadFromFile("arial.ttf");
	content_.setFont(font_);
	content_.setString("");
	content_.setCharacterSize(character_size);
	content_.setOutlineColor(sf::Color::White);
	content_.setFillColor(sf::Color::White);
	content_.setPosition(screen_position + offset);

	backdrop_.setSize(sf::Vector2f(350, 5 * character_size * 1.2f));
	backdrop_.setFillColor(sf::Color(90, 90, 90, 90));
	backdrop_.setPosition(screen_position);
}

void UserInterfaceSystem::Render(Window& window)
{
	std::string content;

	for (auto& itr : messages_)
	{
		content.append(itr + "\n");
	}

	if (content != "")
	{
		content_.setString(content);
		window.window()->draw(backdrop_);
		window.window()->draw(content_);
	}
}

void UserInterfaceSystem::on_message_event(const MessageEvent& event)
{
	messages_.push_back(event.message_);
	if (messages_.size() > 6)
	{
		messages_.erase(messages_.begin());
	}
}