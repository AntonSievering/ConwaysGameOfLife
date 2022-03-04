#pragma once

#include "UserInterface.h"
#include "../Engine.h"


namespace Engine
{
	namespace GUI
	{
		class MainUserInterface : public GUI::UserInterface
		{
		private:
			PixelEngine *m_pEngine = nullptr;

		public:
			MainUserInterface() noexcept : UserInterface() {};

			MainUserInterface(const vf2d &pos, const vf2d &size, PixelEngine *e) noexcept
			{
				this->pos = pos;
				this->size = size;
				m_pEngine = e;
			}

			~MainUserInterface() noexcept override {}

		public:
			void render() noexcept
			{
				if (getDerived() != nullptr)
					getDerived()->render(m_pEngine);
			}
		};
	}
}
