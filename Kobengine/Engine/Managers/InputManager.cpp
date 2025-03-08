#include <SDL.h>
#include "InputManager.h"

#include <memory>

#include "backends/imgui_impl_sdl2.h"

bool kob::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return false;

		// Process Events for ImGui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	ProcessKeyboard();
	ProcessGamepad();

	return true;
}

void kob::InputManager::RegisterGamepadButton(WORD button, std::unique_ptr<Command> cmd, TriggerState state)
{
    m_GamepadMappings[button].command = std::move(cmd);
    m_GamepadMappings[button].state = state;
}

void kob::InputManager::RegisterKeyboardKey(SDL_KeyCode key, std::unique_ptr<Command> cmd, TriggerState state)
{
    m_KeyboardMappings[key].command = std::move(cmd);
    m_KeyboardMappings[key].state = state;
}

void kob::InputManager::ProcessKeyboard()
{
    const Uint8* currentKeyboard = SDL_GetKeyboardState(nullptr);

    for (const auto& input : m_KeyboardMappings)
    {
        const auto& keycode = input.first;
		const SDL_Scancode key = SDL_GetScancodeFromKey(keycode);
        const auto& state = input.second.state;
        const auto& command = input.second.command;

        switch (state)
        {
        case TriggerState::Pressed:
            if (m_PreviousKeyboardStates[key] == 0 && currentKeyboard[key] == 1) command->Execute();
            break;

        case TriggerState::Released:
            if (m_PreviousKeyboardStates[key] == 1 && currentKeyboard[key] == 0) command->Execute();
            break;

        case TriggerState::Down:
            if (currentKeyboard[key]) command->Execute();
            break;
        }
    }

    memcpy(m_PreviousKeyboardStates, currentKeyboard, SDL_NUM_SCANCODES);
}

void kob::InputManager::ProcessGamepad()
{
	m_Gamepad.Update();
	for (const auto& input : m_GamepadMappings)
	{
		const auto& button = input.first;
		const auto& state = input.second.state;
		const auto& command = input.second.command;

		switch (state)
		{
		case TriggerState::Pressed:
			if (m_Gamepad.IsButtonPressed(button)) command->Execute();
			break;
		case TriggerState::Down:
			if (m_Gamepad.IsButtonDown(button)) command->Execute();
			break;
		case TriggerState::Released:
			if (m_Gamepad.IsButtonReleased(button)) command->Execute();
			break;
		}
	}
}
