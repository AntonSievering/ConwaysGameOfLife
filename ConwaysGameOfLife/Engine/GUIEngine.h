#include "Engine.h"
#include "GUI/MainUserInterface.h"

// todo: BaseWindow class
//       -> UserInterface
//       -> MainUserInterface

namespace Engine
{
	class GUIEngine : public PixelEngine
	{
	private:
		GUI::MainUserInterface m_uiMainUserInterface = GUI::MainUserInterface({ -1.0f, -1.0f }, { 2.0f, 2.0f }, this);

	public:
		GUIEngine() noexcept : PixelEngine() {};

		// GUI Integration
	public:
		void attachUserInterface(GUI::UserInterface *pUi) noexcept
		{
			m_uiMainUserInterface.getEndpoint()->derive(pUi);
		}

		const GUI::MainUserInterface &getMainUserInterface() const noexcept
		{
			return m_uiMainUserInterface;
		}

		bool isEndpoint() const noexcept
		{
			return m_uiMainUserInterface.isEndpoint();
		}

		HWKey GetKey(const Key &key) const noexcept override
		{
			return m_uiMainUserInterface.getKey(key);
		}

	private:
		virtual void UpdateInternals() noexcept override
		{
			m_uiMainUserInterface.getEndpoint()->setKeys(m_vKeyManager);
			m_uiMainUserInterface.update(this);
		}

		virtual void RenderInternals() noexcept override
		{
			m_uiMainUserInterface.render();
		}
	};
}
