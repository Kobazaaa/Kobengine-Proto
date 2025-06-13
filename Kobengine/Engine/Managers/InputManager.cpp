#include <SDL.h>
#include <memory>
#include "backends/imgui_impl_sdl2.h"
#include "InputManager.h"


//--------------------------------------------------
//    Loop
//--------------------------------------------------
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
	for (auto& gamepad : m_vGamepads)
		ProcessGamepad(gamepad->GetGamepadID());

	return true;
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
void kob::InputManager::ProcessGamepad(int gamepadID)
{
	auto& gamepad = m_vGamepads[gamepadID];
	gamepad->Update();

	const auto& mapping = m_vGamepadMappings[gamepadID];
	for (const auto& input : mapping)
	{
		const auto& button = input.first;
		const auto& state = input.second.state;
		const auto& command = input.second.command;

		switch (state)
		{
		case TriggerState::Pressed:
			if (gamepad->IsButtonPressed(button)) command->Execute();
			break;
		case TriggerState::Down:
			if (gamepad->IsButtonDown(button)) command->Execute();
			break;
		case TriggerState::Released:
			if (gamepad->IsButtonReleased(button)) command->Execute();
			break;
		}
	}
}


//--------------------------------------------------
//    Registration of Commands
//--------------------------------------------------
void kob::InputManager::RegisterGamepadCmd(Gamepad::Button button, TriggerState state, std::unique_ptr<Command> upCommand, int gamepadID)
{
	m_vGamepadMappings[gamepadID][button].command = std::move(upCommand);
	m_vGamepadMappings[gamepadID][button].state = state;
}
void kob::InputManager::RegisterKeyboardCmd(SDL_KeyCode key, TriggerState state, std::unique_ptr<Command> upCommand)
{
	m_KeyboardMappings[key].command = std::move(upCommand);
	m_KeyboardMappings[key].state = state;
}

void kob::InputManager::UnregisterGamepadBtn(Gamepad::Button button, int gamepadID)
{
	m_vGamepadMappings[gamepadID].erase(button);
}
void kob::InputManager::UnregisterKeyboardKey(SDL_KeyCode key)
{
	m_KeyboardMappings.erase(key);
}
void kob::InputManager::UnregisterAll(bool keyboard, bool gamepad)
{
	if (keyboard)
		m_KeyboardMappings.clear();
	if (gamepad)
		m_vGamepadMappings.clear();
}

void kob::InputManager::RegisterGamepad()
{
	int index = static_cast<int>(m_vGamepads.size());
	m_vGamepads.push_back(std::make_unique<Gamepad>(index));
}
const kob::Gamepad* kob::InputManager::GetGamepad(int gamepadID) const
{
	if (std::ranges::find_if(m_vGamepads, [gamepadID](const std::unique_ptr<Gamepad>& pad) { return pad->GetGamepadID() == gamepadID; }) == m_vGamepads.end())
		return nullptr;
	return m_vGamepads.at(gamepadID).get();
}
