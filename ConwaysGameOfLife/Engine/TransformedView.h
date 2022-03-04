#pragma once

#include "vec2d.h"

namespace Engine
{
	class TransformedView
	{
	private:
		vf2d  m_vPanOffset{};
		float m_fZoom = 1.0f;

	public:
		TransformedView() noexcept = default;

		TransformedView(const vf2d &vPanOffset, const float fZoom)
		{
			m_vPanOffset = vPanOffset;
			m_fZoom      = fZoom;
		}

	public:
		vf2d worldToScreen(const vf2d &pos) const noexcept
		{
			return (pos - m_vPanOffset) * m_fZoom;
		}

		vf2d screenToWorld(const vf2d &pos) const noexcept
		{
			return pos / m_fZoom + m_vPanOffset;
		}

		void zoom(const float fFactor, const vf2d &vAround) noexcept
		{
			vf2d vMouseBeforeZoom = screenToWorld(vAround);
			m_fZoom *= fFactor;
			vf2d vMouseAfterZoom = screenToWorld(vAround);
			m_vPanOffset += vMouseBeforeZoom - vMouseAfterZoom;
		}

		void pan(const vf2d &vOffset) noexcept
		{
			m_vPanOffset -= vOffset / m_fZoom;
		}

	public:
		float getZoom() const noexcept
		{
			return m_fZoom;
		}

		void setZoom(const float fZoom) noexcept
		{
			m_fZoom = fZoom;
		}

		vf2d getPanOffset() const noexcept
		{
			return m_vPanOffset;
		}

		void setPanOffset(const vf2d &vPanOffset) noexcept
		{
			m_vPanOffset = vPanOffset;
		}
	};
}
