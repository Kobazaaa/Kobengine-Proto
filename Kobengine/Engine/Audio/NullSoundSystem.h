#pragma once
#include <filesystem>
#include "ISoundSystem.h"

namespace kob
{
	class NullSoundSystem final : public ISoundSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		NullSoundSystem() = default;

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		AudioClip& Load(const std::filesystem::path&) override { return m_EmptyClip; };
		void Play(const std::filesystem::path&, float, int) override {};
		void Pause(const std::filesystem::path&) override {};
		void PauseAll() override {};
		void Resume(const std::filesystem::path&) override {};
		void ResumeAll() override {};
		void Stop(const std::filesystem::path&) override {};
		void StopAll() override {};

		//--------------------------------------------------
		//    NullAudioClip
		//--------------------------------------------------
		struct NullAudioClip final : public AudioClip
		{
			NullAudioClip() = default;

			void Play(float, int)	override { }
			void Pause()			override { }
			void Resume()			override { }
			void Stop()				override { }
		};
	private:
		NullAudioClip m_EmptyClip{};
	};
}
