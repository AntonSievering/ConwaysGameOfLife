#pragma once

#include <cstdint>
#include <memory>
#include <iostream>

namespace Engine
{
	template <class T>
	class Array1D
	{
	private:
		std::shared_ptr<T[]> m_pData = nullptr;
		size_t               m_nSize = 0;

	public:
		Array1D() noexcept = default;

		Array1D(const size_t nLength) noexcept
		{
			m_pData = std::shared_ptr<T[]>(new T[nLength]{});
			m_nSize = nLength;
		}

		Array1D(T *data, const size_t nLength) noexcept
		{
			m_pData = std::shared_ptr<T[]>(data);
			m_nSize = nLength;
		}

	public:
		T *data() noexcept
		{
			return m_pData.get();
		}

		T *data() const noexcept
		{
			return m_pData.get();
		}

		size_t size() const noexcept
		{
			return m_nSize;
		}

		T &operator[](const size_t index) noexcept
		{
			return data()[index];
		}

		T &at(const size_t index) noexcept
		{
			return operator[](index);
		}

		const T &operator[](const size_t index) const noexcept
		{
			return data()[index];
		}

		const T &at(const size_t index) const noexcept
		{
			return operator[](index);
		}
	};
}
