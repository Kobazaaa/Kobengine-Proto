#pragma once
#include <chrono>

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

namespace rib
{
	class Timer final
	{
	public:
		//--------------------------------------------------
		//    Constructors and Destructors
		//--------------------------------------------------
		Timer() = delete;
		~Timer() = delete;

		Timer(const Timer& other) = delete;
		Timer(Timer&& other) = delete;
		Timer& operator=(const Timer& other) = delete;
		Timer& operator=(Timer&& other) = delete;


		//--------------------------------------------------
		//    Behavioural
		//--------------------------------------------------
		static void Start();
		static void Update();

		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		[[nodiscard]] static  bool DoFixedTimeStep();
		[[nodiscard]] static float GetDeltaSeconds();
		[[nodiscard]] static float GetTotalTimeSeconds();
		[[nodiscard]] static float GetFixedDeltaSeconds();

	private:
		//--------------------------------------------------
		//    Time Variables
		//--------------------------------------------------
		// Immutable
		static constexpr float	FIXED_TIME_STEP_SECONDS	{ 0.02f };
		static constexpr float	TARGET_FPS				{ 60.f };

		// Mutable
		inline static float				m_TotalTimeSeconds{};
		inline static float				m_DeltaTimeSeconds{};
		inline static float				m_LagTimeSeconds{};
		inline static float				m_SleepTimeSeconds{};

		inline static int				m_Ticks{};

		inline static TimePoint			m_CurrentTimePoint{};
		inline static TimePoint			m_LastTimePoint{};
	};
}