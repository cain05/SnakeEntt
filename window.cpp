#include "window.h"

Window::Window()
{
	Setup("window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u size)
{
	Setup(title, size);
}

Window::~Window()
{
	Destroy();
}

void Window::Setup(const std::string& title, const sf::Vector2u size)
{
	window_title_ = title;
	window_size_ = size;
	is_fullscreen_ = false;
	is_done_ = false;
	Create();
}

void Window::Create()
{
	auto style = (is_fullscreen_ ? sf::Style::Fullscreen : sf::Style::Default);
	window_.create({ window_size_.x, window_size_.y, 32 }, window_title_, style);
}

void Window::Destroy()
{
	window_.close();
}

void Window::Update()
{
	sf::Event event;
	while (window_.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			is_done_ = true;
		}
		else if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F5)
		{
			ToggleFullscreen();
		}
	}
}

void Window::BeginDraw()
{
	window_.clear({ sf::Color::Black });
}

void Window::EndDraw()
{
	window_.display();
}

bool Window::is_done() noexcept
{
	return is_done_;
}

bool Window::is_fullscreen() noexcept
{
	return is_fullscreen_;
}

sf::Vector2u Window::window_size() noexcept
{
	return window_size_;
}

void Window::Draw(sf::Drawable& drawable)
{
	window_.draw(drawable);
}

void Window::ToggleFullscreen()
{
	is_fullscreen_ = !is_fullscreen_;
	Destroy();
	Create();
}

sf::RenderWindow* Window::window()
{
	return &window_;
}