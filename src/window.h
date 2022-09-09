#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Window final
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u size);
	virtual ~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool is_done() noexcept;
	bool is_fullscreen() noexcept;
	sf::Vector2u window_size() noexcept;

	void ToggleFullscreen();
	void Draw(sf::Drawable& drawable);

	sf::RenderWindow* window();

private:

	void Setup(const std::string& title, const sf::Vector2u size);
	void Destroy();
	void Create();

	sf::RenderWindow window_;
	sf::Vector2u window_size_;
	std::string window_title_;
	bool is_done_;
	bool is_fullscreen_;
};