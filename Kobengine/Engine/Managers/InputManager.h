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

		void RegisterGamepadCmd(Gamepad::Button button, TriggerState state, std::unique_ptr<Command> upCommand, int gamepadID);
		void RegisterKeyboardCmd(SDL_KeyCode key, TriggerState state, std::unique_ptr<Command> upCommand);
		void UnregisterGamepadBtn(Gamepad::Button button, int gamepadID);
		void UnregisterKeyboardKey(SDL_KeyCode key);

		void RegisterGamepad();
		const Gamepad* GetGamepad(int gamepadID) const;
	private:
		void ProcessKeyboard();
		void ProcessGamepad(int gamepadID);

		struct InputDetails
		{
			TriggerState state;
			std::unique_ptr<Command> command;
		};

		// Gamepad
		using Mapping = std::unordered_map<Gamepad::Button, InputDetails>;
		std::vector<std::unique_ptr<Gamepad>> m_vGamepads{};
		std::unordered_map<int, Mapping> m_vGamepadMappings;

		// Keyboard
		std::unordered_map<SDL_KeyCode, InputDetails> m_KeyboardMappings;

		Uint8 m_PreviousKeyboardStates[SDL_NUM_SCANCODES] = {0};
	};

}
