#pragma once
#include <vector>
#include "EventListeners.h"
#include "GameObject.h"

namespace kob
{
	template<typename... Args>
	class Event final
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		Event() = default;
		virtual ~Event() = default;

		Event(const Event& other) = delete;
		Event(Event&& other) noexcept = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) noexcept = delete;

		//--------------------------------------------------
		//    Event
		//--------------------------------------------------
		void AddListener(const std::shared_ptr<EventListener<Args...>>& listener)
		{
			if (!listener) return;
			if (std::ranges::find(m_pEventListeners, listener) == m_pEventListeners.end())
			{
				m_pEventListeners.push_back(listener);
			}
		}
		void RemoveListener(const std::shared_ptr<EventListener<Args...>>& listener)
		{
			std::erase_if(m_pEventListeners, [&](const EventListener<Args...>* l) { return l == listener; });
		}
		void RemoveAllListeners()
		{
			m_pEventListeners.erase(m_pEventListeners.begin(), m_pEventListeners.end());
			m_pEventListeners.clear();
		}
		void Invoke(Args... args)
		{
			if (m_pEventListeners.empty()) return;
			for (const auto& listener : m_pEventListeners)
			{
				listener->Notify(args...);
			}
		}


		//--------------------------------------------------
		//    Operator Overloading
		//--------------------------------------------------
		void operator+=(const std::shared_ptr<EventListener<Args...>>& listener) { AddListener(listener); }
		void operator-=(const std::shared_ptr<EventListener<Args...>>& listener) { RemoveListener(listener); }
		void operator()(Args... args)											 { Invoke(args...); }

	private:
		std::vector<std::shared_ptr<EventListener<Args...>>> m_pEventListeners{};
	};
}
