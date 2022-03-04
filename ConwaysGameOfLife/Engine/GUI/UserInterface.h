#pragma once

#include "Label.h"
#include "../KeyManager.h"
#include "Button.h"
#include "Picture.h"

namespace Engine
{
	namespace GUI
	{
		constexpr float g_fHeadingHeight = 0.05f; // 2.5 % of the screen height

		class UserInterface : public Widget
		{
		private:
			UserInterface                 *m_pParent       = nullptr;
			std::unique_ptr<UserInterface> m_pDerived      = nullptr;
			BasePanel                      m_pBackground{};
			Label                          m_lblHeading{};
			std::unique_ptr<Button>        m_btnClose      = nullptr;
			bool                           m_bRequestClose = false;
			KeyManager                     m_vKeys{};

		public:
			UserInterface() noexcept : Widget() {}

			UserInterface(const vf2d &pos, const vf2d &size, const std::string &sTitle, const Pixel &pxBackgroundColour = WHITE, const Pixel &pxTitleColour = BLACK) noexcept
				: Widget(pos, size)
			{
				createHeading(sTitle, pxTitleColour);
				m_pBackground = Panel(pos, size, pxBackgroundColour);
			}

			UserInterface(const vf2d &pos, const vf2d &size, const std::string &sTitle, const Sprite2D &sprBackground, const Pixel &pxTitleColour = BLACK) noexcept
				: Widget(pos, size)
			{
				createHeading(sTitle, pxTitleColour);
				m_pBackground = Picture(sprBackground, pos, size);
			}

			UserInterface(const vf2d &pos, const vf2d &size, const std::string &sTitle, const ButtonSprites &sprites, const Pixel &pxBackgroundColour = WHITE, const Pixel &pxTitleColour = BLACK) noexcept
				: UserInterface(pos, size, sTitle, pxBackgroundColour, pxTitleColour)
			{
				createCloseButton(sprites);
			}

			UserInterface(const vf2d &pos, const vf2d &size, const std::string &sTitle, const ButtonSprites &sprites, const Sprite2D &sprBackground, const Pixel &pxTitleColour = BLACK) noexcept
				: UserInterface(pos, size, sTitle, sprBackground, pxTitleColour)
			{
				createCloseButton(sprites);
			}

			virtual ~UserInterface() noexcept
			{
				if (m_pParent)
					m_pParent->notifyDerivedClosed();
			}

		private:
			void createHeading(const std::string &sTitle, const Pixel &pxTitleColour) noexcept
			{
				vf2d vHeadingSize = vf2d(size.x - g_fHeadingHeight, g_fHeadingHeight);
				vf2d vHeadingPos = vf2d(pos.x, pos.y + size.y - vHeadingSize.y);
				m_lblHeading = Label(vHeadingPos, vHeadingSize, sTitle, pxTitleColour, Alignment::LEFT);
			}

			void createCloseButton(const ButtonSprites &sprites) noexcept
			{
				vf2d vButtonSize = vf2d(g_fHeadingHeight, g_fHeadingHeight);
				vf2d vButtonPos = pos + size - vButtonSize;
				m_btnClose = std::make_unique<Button>(sprites, vButtonPos, vButtonSize, Activation::RELEASE);
			}

		public:
			void notifyDerivedClosed() noexcept
			{
				m_pDerived = nullptr;
			}

			void setParent(UserInterface *pUi) noexcept
			{
				m_pParent = pUi;
			}

			void derive(UserInterface *pUi) noexcept
			{
				m_pDerived = std::unique_ptr<UserInterface>(pUi);
				m_pDerived->setParent(this);
				resetKeys();
			}

			UserInterface *getEndpoint() noexcept
			{
				if (m_pDerived == nullptr)
					return this;

				return m_pDerived->getEndpoint();
			}

			bool isEndpoint() const noexcept
			{
				return m_pDerived == nullptr;
			}

			UserInterface *getParent() noexcept
			{
				return m_pParent;
			}

			UserInterface *getDerived() noexcept
			{
				return m_pDerived.get();
			}

			void update(Engine::PixelEngine *engine) noexcept override
			{
				if (m_btnClose != nullptr)
					if (m_btnClose->isPressed(engine->GetMouse(), getKey(Key::MOUSE_LEFT)))
					{
						m_bRequestClose = true;
						return m_pParent->update(engine);
					}

				if (m_pDerived)
				{
					if (m_pDerived->requestsClose())
						notifyDerivedClosed();
					else
						m_pDerived->update(engine);
				}
			}

			void render(PixelEngine *engine) noexcept
			{
				m_pBackground.render(engine, isEndpoint(), m_vKeys);
				m_lblHeading.render(engine, isEndpoint(), m_vKeys);

				if (m_btnClose != nullptr)
					m_btnClose->render(engine, isEndpoint(), m_vKeys);

				if (m_pDerived)
					m_pDerived->render(engine);
			}

			void setKeys(const KeyManager &vKeys) noexcept
			{
				m_vKeys = vKeys;
			}

			void resetKeys() noexcept
			{
				m_vKeys.resetKeys();
			}

			HWKey getKey(const Key &key) const noexcept
			{
				return m_vKeys.getKey(key);
			}

			bool requestsClose() const noexcept
			{
				return m_bRequestClose;
			}
		};
	}
}
