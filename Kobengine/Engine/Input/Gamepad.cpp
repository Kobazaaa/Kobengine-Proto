#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#include "Gamepad.h"


//--------------------------------------------------
//    PIMPL
//--------------------------------------------------
class kob::Gamepad::GamepadImpl final
{
public:
	//--------------------------------------------------
	//    Constructor
	//--------------------------------------------------
	explicit Gamepad::GamepadImpl(int controllerIndex)
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
	bool IsButtonPressed(WORD button) const
	{
		return m_ButtonsPressed & button;
	}
	bool IsButtonDown(WORD button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}
	bool IsButtonReleased(WORD button) const
	{
		return m_ButtonsReleased & button;
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
	: m_pImpl{ new GamepadImpl(controllerIndex) }
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
bool kob::Gamepad::IsButtonPressed(unsigned short button) const
{
	return m_pImpl->IsButtonPressed(button);
}
bool kob::Gamepad::IsButtonDown(unsigned short button) const
{
	return m_pImpl->IsButtonDown(button);
}
bool kob::Gamepad::IsButtonReleased(unsigned short button) const
{
	return m_pImpl->IsButtonReleased(button);
}
