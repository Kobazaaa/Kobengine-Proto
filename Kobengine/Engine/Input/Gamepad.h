#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

namespace kob
{
	class Gamepad final
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit Gamepad(int controllerIndex);


		//--------------------------------------------------
		//    Update
		//--------------------------------------------------
		void Update();


		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		bool IsConnected() const;
		bool IsButtonPressed(WORD button) const;
		bool IsButtonDown(WORD button) const;
		bool IsButtonReleased(WORD button) const;

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
}
