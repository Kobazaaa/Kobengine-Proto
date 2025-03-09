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
		enum class Button;
		bool IsConnected() const;
		bool IsButtonPressed(Button button) const;
		bool IsButtonDown(Button button) const;
		bool IsButtonReleased(Button button) const;


		//--------------------------------------------------
		//    Buttons
		//--------------------------------------------------
		enum class Button
		{
			// Buttons
			A,
			B,
			X,
			Y,

			// Bumpers
			LEFT_BUMPER,
			RIGHT_BUMPER,

			// 
			BACK,
			START,

			// Thumb Buttons
			LEFT_THUMB,
			RIGHT_THUMB,

			// DPAD
			DPAD_UP,
			DPAD_DOWN,
			DPAD_LEFT,
			DPAD_RIGHT
		};

	private:
		class GamepadXInputImpl;
		GamepadXInputImpl* m_pImpl;
	};
}
