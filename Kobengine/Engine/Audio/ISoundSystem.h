#pragma once
#include <memory>
#include <string>

namespace kob
{
	class ISoundSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		virtual ~ISoundSystem() = default;

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		struct AudioClip
		{
			virtual ~AudioClip() = default;

			virtual void Play(float volume, int loops) = 0;
			virtual void Pause() = 0;
			virtual void Resume() = 0;
			virtual void Stop() = 0;
		};

		virtual AudioClip& Load(const std::filesystem::path& file) = 0;
		virtual void Play(const std::filesystem::path& file, float volume, int loops = 0) = 0;
		virtual void Pause(const std::filesystem::path& file) = 0;
		virtual void PauseAll() = 0;
		virtual void Resume(const std::filesystem::path& file) = 0;
		virtual void ResumeAll() = 0;
		virtual void Stop(const std::filesystem::path& file) = 0;
		virtual void StopAll() = 0;
		virtual void SetGlobalVolumeScale(float scale) = 0;
	};
}
