#pragma once

#include "VertexBuffer.h"
#include "SpriteShader.h"
#include "TransformedView.h"
#include <string>
#include <vector>

namespace Engine
{
	class StringDecal
	{
		VertexbufferSprite2D m_vertexBuffer{};

	public:
		StringDecal() noexcept = default;

		StringDecal(const std::string &str, const Engine::vf2d &pos, const float &fScale) noexcept
		{
			setString(str, pos, fScale);
		}

	public:
		void setString(const std::string &sText, const Engine::vf2d &pos, const float &fScale) noexcept
		{
			std::vector<Vertex2D> vVertices;

			vi2d vOffset{};
			const vf2d vBlockSize = vf2d(fScale * 0.01f, fScale * 0.02f);

			const float fTxOffset = 1.0f / 16.0f;

			for (const char &idx : sText)
			{
				const vi2d vAsciiIndex = vi2d(idx % 16, idx / 16);
				const vf2d vFrom       = vf2d((float)vAsciiIndex.x / 16.0f, 1.0f - (float)vAsciiIndex.y / 16.0f);
				const vf2d vTo         = vf2d(vFrom.x + fTxOffset, vFrom.y - fTxOffset);

				const vf2d vCharacterPos = pos + vf2d((float)vOffset.x * vBlockSize.x, (float)vOffset.y * vBlockSize.y);

				vVertices.push_back({ vCharacterPos.x,                vCharacterPos.y,                vFrom.x, vFrom.y });
				vVertices.push_back({ vCharacterPos.x,                vCharacterPos.y - vBlockSize.y, vFrom.x, vTo.y   });
				vVertices.push_back({ vCharacterPos.x + vBlockSize.x, vCharacterPos.y - vBlockSize.y, vTo.x,   vTo.y   });
				vVertices.push_back({ vCharacterPos.x,                vCharacterPos.y,                vFrom.x, vFrom.y });
				vVertices.push_back({ vCharacterPos.x + vBlockSize.x, vCharacterPos.y - vBlockSize.y, vTo.x,   vTo.y   });
				vVertices.push_back({ vCharacterPos.x + vBlockSize.x, vCharacterPos.y,                vTo.x,   vFrom.y });

				if (idx == '\n')
				{
					vOffset.x = 0;
					vOffset.y--;
				}
				else
				{
					vOffset.x++;
				}
			}

			m_vertexBuffer = VertexbufferSprite2D(vVertices);
		}

		void render(const SpriteShader shader, const Pixel &col = Engine::WHITE) const noexcept
		{
			shader.setColour(col);
			shader.resetTranform();
			m_vertexBuffer.render();
		}

		void renderWorld(const SpriteShader &shader, const TransformedView &tv, const Pixel &col = Engine::WHITE) const noexcept
		{
			shader.setColour(col);
			shader.setTransform(tv.getPanOffset(), tv.getZoom());
			m_vertexBuffer.render();
		}

		static vf2d getStringSize(const std::string &sText) noexcept
		{
			uint32_t nLineFeeds = 1;
			uint32_t nLongest   = 0;
			uint32_t nCurrent   = 0;

			for (const char &c : sText)
			{
				if (c == '\n')
				{
					nLineFeeds++;

					if (nCurrent > nLongest)
					{
						nLongest = nCurrent;
						nCurrent = 0;
					}
				}
				else
					nCurrent++;
			}

			if (nCurrent > nLongest)
				nLongest = nCurrent;

			return { 0.01f * nLongest, 0.02f * nLineFeeds };
		}
	};
}
