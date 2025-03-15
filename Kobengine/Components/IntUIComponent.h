#pragma once
#include <memory>
#include <sstream>

#include "Component.h"
#include "Event.h"

namespace kob
{
	class TextRendererComponent;

	class IntUIComponent final : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit IntUIComponent(GameObject& parent, const std::string& prefix, int initialValue, const std::string& postfix, Event<int>& listenEvent);


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;


		//--------------------------------------------------
		//    Event
		//--------------------------------------------------
		void OnValueChange(int value) const;

	private:
		std::string m_Prefix{};
		std::string m_Postfix{};
		TextRendererComponent* m_pTextRenderer;

		EventCallback<int> m_pEventCallback = EventCallback(this, &IntUIComponent::OnValueChange);
	};
}
