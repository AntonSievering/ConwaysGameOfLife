#pragma once

#include "Engine/Engine.h"
#include "Engine/Array2D.h"

class GameOfLife : public Engine::PixelEngine
{
private:
	constexpr static Engine::vu2d g_s_vSize = { 800, 500 };
	Engine::Array2D<bool> m_gameBoard;
	Engine::Array2D<bool> m_calculateBuffer;
	Engine::Sprite2D m_gameSprite;
	Engine::Decal m_gameDecal;
	Engine::TransformedView m_tv;
	Engine::vf2d m_vPanStart;
	bool bUpdateScreen = true;

public:
	GameOfLife()
	{
		m_sAppName = "John Conway's Game Of Life";
	}

public:
	bool OnUserCreate() noexcept override
	{
		m_gameBoard = Engine::Array2D<bool>(g_s_vSize);
		m_calculateBuffer = Engine::Array2D<bool>(g_s_vSize);
		m_gameSprite = Engine::Sprite2D(g_s_vSize);
		Engine::vf2d vSize = getAspectRatio().scaleAlongWidth(Engine::vf2d((float)g_s_vSize.x, (float)g_s_vSize.y));
		m_gameDecal = Engine::Decal(m_gameSprite, { 0.0f, 0.0f }, vSize);
		m_tv.setZoom(0.01f);
		m_tv.setPanOffset({ 100.0f, 50.0f });

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) noexcept override
	{
		if (GetKey(Engine::Key::Q).bHeld) m_tv.zoom(1.0f + fElapsedTime, GetMouse());
		if (GetKey(Engine::Key::E).bHeld) m_tv.zoom(1.0f / (1.0f + fElapsedTime), GetMouse());

		Engine::vf2d vfCoordinate = getAspectRatio().reverseScaleAlongWidth(m_tv.screenToWorld(GetMouse()));
		Engine::vi2d viCoordinate = Engine::vi2d(std::floor(vfCoordinate.x), std::floor(vfCoordinate.y));

		if (GetKey(Engine::Key::MOUSE_LEFT).bPressed)
			if (viCoordinate.x >= 0 && viCoordinate.y >= 0 && viCoordinate.x < g_s_vSize.x && viCoordinate.y < g_s_vSize.y)
			{
				m_gameBoard.at(viCoordinate.x, viCoordinate.y) = !m_gameBoard.at(viCoordinate.x, viCoordinate.y);
				bUpdateScreen = true;
			}

		if (GetKey(Engine::Key::SPACE).bHeld) // update field
		{
			bUpdateScreen = true;

			for (uint32_t i = 1; i < g_s_vSize.x - 1; i++)
			{
				for (uint32_t j = 1; j < g_s_vSize.y - 1; j++)
				{
					int cellCount = 0;
					for (uint32_t ii = i - 1; ii <= i + 1; ii++)
					{
						for (uint32_t jj = j - 1; jj <= j + 1; jj++)
						{
							cellCount += m_gameBoard.at({ ii, jj });
						}
					}
					cellCount -= m_gameBoard.at({ i, j });

					if (m_gameBoard.at({ i, j })) // live cell
					{
						if (cellCount == 2 || cellCount == 3) // live
							m_calculateBuffer.at({ i, j }) = true;
						else // die
							m_calculateBuffer.at({ i, j }) = false;
					}
					else // dead cell
					{
						if (cellCount == 3) // live
							m_calculateBuffer.at({ i, j }) = true;
						else // die
							m_calculateBuffer.at({ i, j }) = false;
					}
				}
			}

			std::swap(m_gameBoard, m_calculateBuffer);
		}

		if (GetKey(Engine::Key::MOUSE_RIGHT).bPressed)
			m_vPanStart = GetMouse();
		else if (GetKey(Engine::Key::MOUSE_RIGHT).bHeld)
		{
			m_tv.pan(GetMouse() - m_vPanStart);
			m_vPanStart = GetMouse();
		}


		if (bUpdateScreen) // update pixel buffer
		{
			for (uint32_t i = 0; i < g_s_vSize.x; i++)
				for (uint32_t j = 0; j < g_s_vSize.y; j++)
					m_gameSprite.getImage().setPixel({ i, j }, m_gameBoard.at({ i, j }) ? Engine::WHITE : Engine::BLACK);
			m_gameSprite.reupload();
			bUpdateScreen = false;
		}

		Clear(Engine::VERY_DARK_BLUE);
		m_gameDecal.renderWorld(getSpriteShader(), m_tv);

		return true;
	}

	bool OnUserDestroy() noexcept override
	{
		return true;
	}
};
