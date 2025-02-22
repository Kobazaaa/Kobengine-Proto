#include "Timer.h"
#include <chrono>

//--------------------------------------------------
//    Behavioural
//--------------------------------------------------
void kob::Timer::Start()
{
	m_LastTimePoint = std::chrono::high_resolution_clock::now();
	m_CurrentTimePoint = std::chrono::high_resolution_clock::now();
	m_DeltaTimeSeconds = 0;
	m_LagTimeSeconds = 0;
	m_SleepTimeSeconds = 0;
}
void kob::Timer::Update()
{
	++m_Ticks;

	m_CurrentTimePoint = std::chrono::high_resolution_clock::now();
	m_DeltaTimeSeconds = std::chrono::duration<float>(m_CurrentTimePoint - m_LastTimePoint).count();
	m_LastTimePoint = m_CurrentTimePoint;
	m_LagTimeSeconds += m_DeltaTimeSeconds;
	m_TotalTimeSeconds += m_DeltaTimeSeconds;
}



//--------------------------------------------------
//    Accessors
//--------------------------------------------------
bool kob::Timer::DoFixedTimeStep()
{
	if (m_LagTimeSeconds >= FIXED_TIME_STEP_SECONDS)
	{
		m_LagTimeSeconds -= FIXED_TIME_STEP_SECONDS;
		return true;
	}

	return false;
}
float kob::Timer::GetDeltaSeconds()
{
	return m_DeltaTimeSeconds;
}
float kob::Timer::GetTotalTimeSeconds()
{
	return m_TotalTimeSeconds;
}
float kob::Timer::GetFixedDeltaSeconds()
{
	return FIXED_TIME_STEP_SECONDS;
}
float kob::Timer::TargetFPS()
{
	return TARGET_FPS;
}
std::chrono::nanoseconds kob::Timer::SleepDurationNanoSeconds()
{
	constexpr auto msPerFrame = std::chrono::milliseconds(static_cast<int>(1'000.f / TARGET_FPS));
	const std::chrono::nanoseconds sleep = (m_CurrentTimePoint + msPerFrame - std::chrono::high_resolution_clock::now());

	return sleep;
}
