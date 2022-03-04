#pragma once
#include "Engine/Engine.h"

class Aliasing : public Engine::PixelEngine
{
private:
	Engine::Sprite2D m_rad;

public:
	Aliasing() noexcept = default;

public:
	bool OnUserCreate() noexcept override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) noexcept override
	{
		return true;
	}

	bool OnUserDestroy() noexcept override
	{
		return true;
	}
};
