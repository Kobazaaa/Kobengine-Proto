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

		void RegisterGamepadCmd(Gamepad::Button button, TriggerState state, std::unique_ptr<Command> upCommand);
		void RegisterKeyboardCmd(SDL_KeyCode key, TriggerState state, std::unique_ptr<Command> upCommand);
		void UnregisterGamepadBtn(Gamepad::Button button);
		void UnregisterKeyboardKey(SDL_KeyCode key);

	private:
		void ProcessKeyboard();
		void ProcessGamepad();

		struct InputDetails
		{
			TriggerState state;
			std::unique_ptr<Command> command;
		};

		Gamepad m_Gamepad{0};
		std::unordered_map<Gamepad::Button, InputDetails> m_GamepadMappings;
		std::unordered_map<SDL_KeyCode, InputDetails> m_KeyboardMappings;

		Uint8 m_PreviousKeyboardStates[SDL_NUM_SCANCODES] = {0};
	};

}
