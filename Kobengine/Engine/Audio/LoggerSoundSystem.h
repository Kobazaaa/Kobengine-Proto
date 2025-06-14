#pragma once
#include <filesystem>
#include "ISoundSystem.h"

namespace kob
{
	class LoggerSoundSystem final : public ISoundSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		LoggerSoundSystem(std::unique_ptr<ISoundSystem>&& ss);

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		AudioClip& Load(const std::filesystem::path& file) override;
		void Play(const std::filesystem::path& file, float volume, int loops) override;
		void Pause(const std::filesystem::path& file) override;
		void PauseAll() override;
		void Resume(const std::filesystem::path& file) override;
		void ResumeAll() override;
		void Stop(const std::filesystem::path& file) override;
		void StopAll() override;
		void SetGlobalVolumeScale(float scale) override;
		float GetGlobalVolumeScale() override;

	private:
		std::unique_ptr<ISoundSystem> m_pRealSoundSystem;
	};
}
