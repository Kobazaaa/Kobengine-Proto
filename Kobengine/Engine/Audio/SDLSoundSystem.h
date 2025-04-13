#pragma once
#include "ISoundSystem.h"

namespace kob
{
	class SDLSoundSystem final : public ISoundSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		SDLSoundSystem();
		~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		void Play() override;

	private:
		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* m_pImpl;
	};
}
