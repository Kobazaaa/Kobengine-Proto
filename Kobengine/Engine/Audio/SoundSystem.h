#pragma once
#include <filesystem>
#include "ISoundSystem.h"

namespace kob
{
	class SoundSystem final : public ISoundSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		SoundSystem(const std::filesystem::path& assetPath);
		~SoundSystem() override;

		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) noexcept = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) noexcept = delete;

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

	private:
		class SoundSystemImpl;
		SoundSystemImpl* m_pImpl;
	};
}
