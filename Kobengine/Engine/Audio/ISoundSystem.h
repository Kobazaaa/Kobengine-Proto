#pragma once

namespace kob
{
	class ISoundSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		ISoundSystem() = default;
		virtual ~ISoundSystem() = default;

		ISoundSystem(const ISoundSystem& other) = delete;
		ISoundSystem(ISoundSystem&& other) noexcept = delete;
		ISoundSystem& operator=(const ISoundSystem& other) = delete;
		ISoundSystem& operator=(ISoundSystem&& other) noexcept = delete;

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		virtual void Play() = 0;
	};
}