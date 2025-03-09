#pragma once
namespace kob
{
	class Gamepad final
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit Gamepad(int controllerIndex);
		~Gamepad();

		Gamepad(const Gamepad& other) = delete;
		Gamepad(Gamepad&& other) noexcept = delete;
		Gamepad& operator=(const Gamepad& other) = delete;
		Gamepad& operator=(Gamepad&& other) noexcept = delete;

		//--------------------------------------------------
		//    Update
		//--------------------------------------------------
		void Update();


		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		bool IsConnected() const;
		bool IsButtonPressed(unsigned short button) const;
		bool IsButtonDown(unsigned short button) const;
		bool IsButtonReleased(unsigned short button) const;

	private:
		class GamepadImpl;
		GamepadImpl* m_pImpl;
	};
}
