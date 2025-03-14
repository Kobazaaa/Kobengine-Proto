#pragma once
#include <functional>
#include <sstream>

#include "TextRendererComponent.h"


namespace kob
{
	template<typename... Args>
	class EventListener
	{
	public:
		virtual ~EventListener() = default;
		virtual void Notify(Args... args) = 0;
	};

	template<typename... Args>
	class EventCallback : public EventListener<Args...>
	{
	public:
		EventCallback(const std::function<void(Args...)>& callback)
		{
			m_Callback = callback;
		}
		virtual void Notify(Args... args) override
		{
			m_Callback(args...);
		}
	private:
		std::function<void(Args...)> m_Callback;
	};

	class HealthUIListener : public EventListener<int>
	{
		TextRendererComponent* m_pTextRenderer{};
	public:
		HealthUIListener(TextRendererComponent& textComp)
			: m_pTextRenderer{ &textComp }
		{ }
		virtual void Notify(int changed) override
		{
			std::stringstream newTxt;
			newTxt << "# lives: ";
			newTxt << changed;
			m_pTextRenderer->SetText(newTxt.str());
		}
	};
	class ScoreUIListener : public EventListener<int>
	{
		TextRendererComponent* m_pTextRenderer{};
	public:
		ScoreUIListener(TextRendererComponent& textComp)
			: m_pTextRenderer{ &textComp }
		{ }
		virtual void Notify(int changed) override
		{
			std::stringstream newTxt;
			newTxt << "Score: ";
			newTxt << changed;
			m_pTextRenderer->SetText(newTxt.str());
		}
	};
}
