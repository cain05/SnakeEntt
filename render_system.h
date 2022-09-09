#pragma once

#include "window.h"
#include <entt/entt.hpp>

class RenderSystem
{
public:
	RenderSystem() = default;
	~RenderSystem() = default;

	void Render(Window& window, entt::registry& registry);
};
