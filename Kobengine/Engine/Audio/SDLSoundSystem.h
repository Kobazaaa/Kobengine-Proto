#pragma once
#include <filesystem>
#include "ISoundSystem.h"

namespace kob
{
	class SDLSoundSystem final : public ISoundSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		SDLSoundSystem(const std::filesystem::path& assetPath);
		~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;

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

	private:
		class SoundSystemImpl;
		SoundSystemImpl* m_pImpl;
	};
}
