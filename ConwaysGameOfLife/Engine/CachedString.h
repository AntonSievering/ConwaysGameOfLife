#pragma once

#include "StringDecal.h"
#include "RenderTarget.h"
#include "Decal.h"

namespace Engine
{
	class CachedString
	{
	private:
		Decal m_decTexture;

	public:
		CachedString() noexcept = default;

		CachedString(const std::string &sText, const vf2d &vPos, const float fSize, const vu2d &vScreenPxSize, const SpriteShader &shader, const Engine::Sprite2D &sprAsciiTable)
		{
			setText(sText, vPos, fSize, vScreenPxSize, shader, sprAsciiTable);
		}

	public:
		void setText(const std::string &sText, const vf2d &vPos, const float fSize, const vu2d &vScreenPxSize, const SpriteShader &shader, const Engine::Sprite2D &sprAsciiTable)
		{
			const vf2d vBaseStringSize    = StringDecal::getStringSize(sText);
			const vf2d vStringSize        = vBaseStringSize * fSize;
			const vu2d vVirtualScreenSize = vStringSize * vScreenPxSize * 0.5f;
			const vf2d vScreenSizeOGL     = ((vf2d)vVirtualScreenSize / (vf2d)vScreenPxSize) * 2.0f - vf2d(1.0f, 1.0f);

			StringDecal decal(sText, { -1.0f, vScreenSizeOGL.y }, fSize);
			
			RenderTarget target = RenderTarget(vVirtualScreenSize, GL_NEAREST, GL_NEAREST);
			target.bind();
			sprAsciiTable.bind();
			decal.render(shader);
			target.unbind();

			m_decTexture = Decal(target.getSprite(), vPos, vStringSize);
		}

		void render(SpriteShader &shader, const Pixel &col = Engine::WHITE) const noexcept
		{
			m_decTexture.render(shader, col);
		}

		Engine::Decal get() const noexcept
		{
			return m_decTexture;
		}
	};
}
