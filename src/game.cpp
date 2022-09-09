#include "game.h"

#include "apple.h"
#include "snake.h"
#include "position.h"
#include "velocity.h"
#include "border.h"

#include "key_pressed_event.h"
#include "snake_hit_wall_event.h"
#include "snake_ate_apple_event.h"
#include "snake_hit_self_event.h"

#include "move_system.h"

Game::Game()
	: window_("Snake ECS", sf::Vector2u(800, 600)),
	elapsed_(0.0f),
	registry_()
{
	//setup borders
	const auto top_border = registry_.create();
	registry_.emplace<Border>(top_border, 0.0f, 0.0f, (float)window_.window_size().x, (float)block_size_);

	const auto left_border = registry_.create();
	registry_.emplace<Border>(left_border, 0.0f, 0.0f, (float)block_size_, (float)window_.window_size().y);

	const auto bottom_border = registry_.create();
	registry_.emplace<Border>(bottom_border, 0.0f, (float)window_.window_size().y - block_size_, (float)window_.window_size().x, (float)block_size_);

	const auto right_border = registry_.create();
	registry_.emplace<Border>(right_border, (float)window_.window_size().x - block_size_, 0.0f, (float)block_size_, (float)window_.window_size().y);

	// setup the apple
	ResetApple();

	// setup the snake
	ResetSnake();

	// move events
	dispatcher_.sink<KeyPressedEvent>().connect<&MoveSystem::on_key_pressed_event>(move_system_);

	//collision events
	dispatcher_.sink<SnakeHitWallEvent>().connect<&Game::on_snake_hit_wall_event>(this);
	dispatcher_.sink<SnakeHitWallEvent>().connect<&MoveSystem::on_snake_hit_wall_event>(move_system_);

	dispatcher_.sink<SnakeAteAppleEvent>().connect<&Game::on_snake_ate_apple_event>(this);
	dispatcher_.sink<SnakeHitSelfEvent>().connect<&Game::on_snake_hit_self_event>(this);

	dispatcher_.sink<MessageEvent>().connect<&UserInterfaceSystem::on_message_event>(user_interface_system_);


	//set up collidables
	collision_holder_.grid_size_x = window_.window_size().x / block_size_;
	collision_holder_.grid_size_y = window_.window_size().y / block_size_;
	collision_holder_.registry = &registry_;

	std::string message = "Seeded random number generator with: " + std::to_string(time(nullptr));
	dispatcher_.trigger<MessageEvent>(message);
}

void Game::Events() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		dispatcher_.trigger<KeyPressedEvent>(KeyPressedEvent{ sf::Keyboard::Up });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		dispatcher_.trigger<KeyPressedEvent>(KeyPressedEvent{ sf::Keyboard::Down });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		dispatcher_.trigger<KeyPressedEvent>(KeyPressedEvent{ sf::Keyboard::Left });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		dispatcher_.trigger<KeyPressedEvent>(KeyPressedEvent{ sf::Keyboard::Right });
	}
}

Window* Game::GetWindow()
{
	return &window_;
}

void Game::Update() {
	window_.Update(); // Update window events.
	float timestep = 1.0f / 15; // snake_.speed();
	if (elapsed_ >= timestep) {
		move_system_.Update(registry_);
		collision_system_.Update(collision_holder_, dispatcher_);
		elapsed_ -= timestep;
	}
}

void Game::Render()
{
	window_.BeginDraw();
	render_system_.Render(window_, registry_);
	user_interface_system_.Render(window_);
	window_.EndDraw();
}

sf::Time Game::GetElapsed()
{
	return clock_.getElapsedTime();
}

void Game::RestartClock()
{
	elapsed_ += clock_.restart().asSeconds();
}

void Game::ResetSnake()
{
	snake_ = registry_.create();
	registry_.emplace<Snake>(snake_, block_size_);
	registry_.emplace<Velocity>(snake_, 15.0f, Direction::None);

	collision_holder_.snake = snake_;
}

void Game::on_snake_hit_wall_event()
{
	registry_.destroy(snake_);
	ResetSnake();
	auto message = std::string("GAME OVER! Score: " + std::to_string(score_));
	dispatcher_.trigger<MessageEvent>(message);
	score_ = 0;
}

void Game::ResetApple()
{
	int max_x = (window_.window_size().x / block_size_) - 2;
	int max_y = (window_.window_size().y / block_size_) - 2;
	auto position = sf::Vector2i(rand() % max_x + 1, rand() % max_y + 1);
	apple_ = registry_.create();
	registry_.emplace<Apple>(apple_, sf::Color::Red, ((float)block_size_ / 2), ((float)position.x * block_size_), ((float)position.y * block_size_));
	registry_.emplace<Position>(apple_, (float)position.x, (float)position.y);

	collision_holder_.apple = apple_;
}

void Game::on_snake_ate_apple_event()
{
	registry_.destroy(apple_);
	ResetApple();
	ExtendSnake();

	score_ += 10;
	auto message = std::string("You ate an apple. Score: " + std::to_string(score_));
	dispatcher_.trigger<MessageEvent>(message);
}

void Game::ExtendSnake()
{
	auto snake = registry_.try_get<Snake>(snake_);
	if (snake != nullptr)
	{
		if (!snake->snake_body_.empty()) {
			SnakeSegment& tail_head =
				snake->snake_body_[snake->snake_body_.size() - 1];
			if (snake->snake_body_.size() > 1) {
				SnakeSegment& tail_bone =
					snake->snake_body_[snake->snake_body_.size() - 2];
				if (tail_head.position_.x == tail_bone.position_.x) {
					if (tail_head.position_.y > tail_bone.position_.y) {
						snake->snake_body_.push_back(SnakeSegment(
							tail_head.position_.x, tail_head.position_.y + 1));
					}
					else {
						snake->snake_body_.push_back(SnakeSegment(
							tail_head.position_.x, tail_head.position_.y - 1));
					}
				}
				else if (tail_head.position_.y == tail_bone.position_.y) {
					if (tail_head.position_.x > tail_bone.position_.x) {
						snake->snake_body_.push_back(SnakeSegment(
							tail_head.position_.x + 1, tail_head.position_.y));
					}
					else {
						snake->snake_body_.push_back(SnakeSegment(
							tail_head.position_.x - 1, tail_head.position_.y));
					}
				}
			}
		}
	}
}

void Game::on_snake_hit_self_event(const SnakeHitSelfEvent& event)
{
	Cut(event.cut_index_);
}

void Game::Cut(int segments) {
	auto snake = registry_.try_get<Snake>(snake_);
	if (snake != nullptr)
	{

		for (int i = 0; i < segments; ++i) {
			snake->snake_body_.pop_back();
		}

		--lives_;

		if (!lives_)
		{
			Lose();
		}
	}
}

void Game::Lose()
{
	score_ = 0;
	lives_ = 3;
	registry_.destroy(apple_);
	registry_.destroy(snake_);
	ResetApple();
	ResetSnake();
}