#pragma once
#include <functional>

namespace kob
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};
	class CommandPFN : public Command
	{
	public:
		explicit CommandPFN(std::function<void()> func)
			: m_Function(std::move(func))
		{ }
		void Execute() override
		{
			if (m_Function)
				m_Function();
		}
	private:
		std::function<void()> m_Function;
	};
}
