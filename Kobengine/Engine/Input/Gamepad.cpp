#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#include "Gamepad.h"


//--------------------------------------------------
//    PIMPL
//--------------------------------------------------
class kob::Gamepad::GamepadXInputImpl final
{
public:
	//--------------------------------------------------
	//    Constructor
	//--------------------------------------------------
	explicit Gamepad::GamepadXInputImpl(int controllerIndex)
		: m_ControllerIndex{ controllerIndex }
	{}

	//--------------------------------------------------
	//    Update
	//--------------------------------------------------
	void Update()
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
	bool IsConnected() const
	{
		return m_IsConnected;
	}
	bool IsButtonPressed(Button button) const
	{
		return m_ButtonsPressed & ToXInputButton(button);
	}
	bool IsButtonDown(Button button) const
	{
		return m_CurrentState.Gamepad.wButtons & ToXInputButton(button);
	}
	bool IsButtonReleased(Button button) const
	{
		return m_ButtonsReleased & ToXInputButton(button);
	}

	//--------------------------------------------------
	//    Conversion
	//--------------------------------------------------
	WORD ToXInputButton(Button button) const
	{
		switch (button)
		{
		case Button::A:					return XINPUT_GAMEPAD_A;
		case Button::B:					return XINPUT_GAMEPAD_B;
		case Button::X:					return XINPUT_GAMEPAD_X;
		case Button::Y:					return XINPUT_GAMEPAD_Y;
		case Button::LEFT_BUMPER:		return XINPUT_GAMEPAD_LEFT_SHOULDER;
		case Button::RIGHT_BUMPER:		return XINPUT_GAMEPAD_RIGHT_SHOULDER;
		case Button::BACK:				return XINPUT_GAMEPAD_BACK;
		case Button::START:				return XINPUT_GAMEPAD_START;
		case Button::LEFT_THUMB:		return XINPUT_GAMEPAD_LEFT_THUMB;
		case Button::RIGHT_THUMB:		return XINPUT_GAMEPAD_RIGHT_THUMB;
		case Button::DPAD_UP:			return XINPUT_GAMEPAD_DPAD_UP;
		case Button::DPAD_DOWN:			return XINPUT_GAMEPAD_DPAD_DOWN;
		case Button::DPAD_LEFT:			return XINPUT_GAMEPAD_DPAD_LEFT;
		case Button::DPAD_RIGHT:		return XINPUT_GAMEPAD_DPAD_RIGHT;
		default: return 0;
		}
	}
private:
	// Index
	int				m_ControllerIndex;

	// States
	XINPUT_STATE	m_CurrentState{};
	XINPUT_STATE	m_PreviousState{};
	WORD			m_ButtonsPressed{};
	WORD			m_ButtonsReleased{};
	bool			m_IsConnected = false;
};





//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::Gamepad::Gamepad(int controllerIndex)
	: m_pImpl{ new GamepadXInputImpl(controllerIndex) }
{}
kob::Gamepad::~Gamepad()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}


//--------------------------------------------------
//    Update
//--------------------------------------------------
void kob::Gamepad::Update()
{
	m_pImpl->Update();
}


//--------------------------------------------------
//    Accessors
//--------------------------------------------------
bool kob::Gamepad::IsConnected() const
{
	return m_pImpl->IsConnected();
}
bool kob::Gamepad::IsButtonPressed(Button button) const
{
	return m_pImpl->IsButtonPressed(button);
}
bool kob::Gamepad::IsButtonDown(Button button) const
{
	return m_pImpl->IsButtonDown(button);
}
bool kob::Gamepad::IsButtonReleased(Button button) const
{
	return m_pImpl->IsButtonReleased(button);
}
