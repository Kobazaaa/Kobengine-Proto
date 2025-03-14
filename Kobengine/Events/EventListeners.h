#pragma once
#include <functional>

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
}
