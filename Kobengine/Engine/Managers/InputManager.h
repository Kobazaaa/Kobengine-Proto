#pragma once
#include <memory>
#include <unordered_map>

#include "Command.h"
#include "Gamepad.h"
#include "Singleton.h"

namespace kob
{
	enum class TriggerState
	{
		Pressed,
		Down,
		Released
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		template<typename CommandType, typename... Args>
			requires std::derived_from<CommandType, Command>
		void RegisterGamepadCmd(unsigned short button, TriggerState state, Args&&... commandArgs)
		{
			m_GamepadMappings[button].command = std::make_unique<CommandType>(std::forward<Args>(commandArgs)...);
			m_GamepadMappings[button].state = state;
		}
		template<typename CommandType, typename... Args>
			requires std::derived_from<CommandType, Command>
		void RegisterKeyboardCmd(SDL_KeyCode key, TriggerState state, Args&&... commandArgs)
		{
			m_KeyboardMappings[key].command = std::make_unique<CommandType>(std::forward<Args>(commandArgs)...);
			m_KeyboardMappings[key].state = state;
		}
	private:
		void ProcessKeyboard();
		void ProcessGamepad();

		struct InputDetails
		{
			TriggerState state;
			std::unique_ptr<Command> command;
		};

		Gamepad m_Gamepad{0};
		std::unordered_map<unsigned short, InputDetails> m_GamepadMappings;
		std::unordered_map<SDL_KeyCode, InputDetails> m_KeyboardMappings;

		Uint8 m_PreviousKeyboardStates[SDL_NUM_SCANCODES] = {0};
	};

}
