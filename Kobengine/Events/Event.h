#pragma once
#include <unordered_set>

#include "EventListeners.h"

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
		~Event()
		{
			for (EventListener<Args...>* listener : m_pEventListeners)
			{
				listener->RemoveEvent(this);
			}
		};

		Event(const Event& other) = delete;
		Event(Event&& other) noexcept = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) noexcept = delete;

		//--------------------------------------------------
		//    Event
		//--------------------------------------------------
		void AddListener(EventListener<Args...>* listener)
		{
			if (!listener) return;

			auto result = m_pEventListeners.insert(listener);
			// Let Listener know if insertion succeeded
			if (result.second)
				listener->AddEvent(this);
		}
		void RemoveListener(EventListener<Args...>* listener)
		{
			if (!listener) return;
			if (m_pEventListeners.empty()) return;

			auto result = m_pEventListeners.erase(listener);
			if (result == 1)
				listener->RemoveEvent(this);
		}
		void RemoveAllListeners()
		{
			for (EventListener<Args...>*& listener : m_pEventListeners)
				listener->RemoveEvent(this);

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
		void operator+=(EventListener<Args...>* listener)		{ AddListener(listener); }
		void operator-=(EventListener<Args...>* listener)		{ RemoveListener(listener); }
		void operator()(Args... args)							{ Invoke(args...); }

	private:
		std::unordered_set<EventListener<Args...>*> m_pEventListeners{};
	};
}
