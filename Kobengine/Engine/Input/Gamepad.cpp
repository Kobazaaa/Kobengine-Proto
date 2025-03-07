#include "Gamepad.h"


//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::Gamepad::Gamepad(int controllerIndex)
	: m_ControllerIndex { controllerIndex }
{}


//--------------------------------------------------
//    Update
//--------------------------------------------------
void kob::Gamepad::Update()
{
	m_ButtonsPressed = 0;
	m_ButtonsReleased = 0;
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(m_ControllerIndex, &m_CurrentState);
	m_IsConnected = result == ERROR_SUCCESS;

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressed = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleased = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}


//--------------------------------------------------
//    Accessors
//--------------------------------------------------
bool kob::Gamepad::IsConnected() const
{
	return m_IsConnected;
}
bool kob::Gamepad::IsButtonPressed(WORD button) const
{
	return m_ButtonsPressed & button;
}
bool kob::Gamepad::IsButtonDown(WORD button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}
bool kob::Gamepad::IsButtonReleased(WORD button) const
{
	return m_ButtonsReleased & button;
}
