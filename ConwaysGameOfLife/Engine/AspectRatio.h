#pragma once

#include "vec2d.h"

namespace Engine
{
	class AspectRatio
	{
	private:
		float m_fAspectRatio = 1.0f; // width / height
		float m_fReverseRatio = 1.0f; // height / width

	public:
		constexpr AspectRatio() noexcept = default;

		constexpr AspectRatio(const float fAspectRatio) noexcept
		{
			m_fAspectRatio = fAspectRatio;
			m_fReverseRatio = 1.0f / fAspectRatio;
		}

	public:
		constexpr inline vf2d scaleAlongWidth(const vf2d &size) const noexcept
		{
			return vf2d(size.x, size.y * m_fAspectRatio);
		}

		constexpr inline vf2d reverseScaleAlongWidth(const vf2d &size) const noexcept
		{
			return vf2d(size.x, size.y * m_fReverseRatio);
		}

		constexpr inline vf2d scaleAlongHeight(const vf2d &size) const noexcept
		{
			return vf2d(size.x * m_fReverseRatio, size.y);
		}

		constexpr inline vf2d reverseScaleAlongHeight(const vf2d &size) const noexcept
		{
			return vf2d(size.x * m_fAspectRatio, size.y);
		}

		constexpr inline float get() const noexcept
		{
			return m_fAspectRatio;
		}
	};
}
