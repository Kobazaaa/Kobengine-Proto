// Kobengine
#include "SoundSystem.h"

// Standard Library
#include <iostream>
#include <unordered_map>

// SDL
#include "SDL.h"
#include "SDL_mixer.h"

//--------------------------------------------------
//    PIMPL
//--------------------------------------------------
class kob::SoundSystem::SoundSystemImpl final
{
public:
	//--------------------------------------------------
	//    Constructor & Destructor
	//--------------------------------------------------
	SoundSystemImpl(std::filesystem::path assetPath)
		: m_AssetPath(std::move(assetPath))
	{
		if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
			std::cerr << "SDL_InitSubSystem failed: " << SDL_GetError() << "\n";

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << "\n";

		int flags = MIX_INIT_MP3 | MIX_INIT_OGG;
		int initializationFlags = Mix_Init(flags);
		if (flags != initializationFlags)
			std::cerr << "Failed to initialize SDL_Mixer";
	}
	~SoundSystemImpl() {	Mix_CloseAudio(); Mix_Quit(); SDL_QuitSubSystem(SDL_INIT_AUDIO); }

	SoundSystemImpl(const SoundSystemImpl& other) = delete;
	SoundSystemImpl(SoundSystemImpl&& other) noexcept = delete;
	SoundSystemImpl& operator=(const SoundSystemImpl& other) = delete;
	SoundSystemImpl& operator=(SoundSystemImpl&& other) noexcept = delete;

	//--------------------------------------------------
	//    Functions
	//--------------------------------------------------
	AudioClip& Load(const std::filesystem::path& file)
	{
		auto fullPath = m_AssetPath / file;
		auto fullPathStr = fullPath.string();

		std::string ext = fullPath.extension().string();
		if (ext == ".wav")
			return *m_mLoadedFX.insert({ fullPathStr, std::make_unique<SDLSound>(fullPath) }).first->second;
		else
			return *m_mLoadedMusic.insert({ fullPathStr, std::make_unique<SDLMusic>(fullPath) }).first->second;
	}

	void Play(const std::filesystem::path& file, float volume, int loops)
	{
		// Loads if not yet loaded, otherwise returns existing clip
		auto& clip = Load(file);
		clip.Play(volume, loops);
	}

	void Pause(const std::filesystem::path& file)
	{
		auto fullPath = (m_AssetPath / file).string();
		if (m_mLoadedFX.contains(fullPath))
		{
			auto& clip = m_mLoadedFX[fullPath];
			clip->Pause();
		}
		if (m_mLoadedMusic.contains(fullPath))
		{
			auto& clip = m_mLoadedMusic[fullPath];
			clip->Pause();
		}
	}
	static void PauseAll()
	{
		Mix_PauseMusic();
		Mix_Pause(-1);
	}

	void Resume(const std::filesystem::path& file)
	{
		auto fullPath = (m_AssetPath / file).string();
		if (m_mLoadedFX.contains(fullPath))
		{
			auto& clip = m_mLoadedFX[fullPath];
			clip->Resume();
		}
		if (m_mLoadedMusic.contains(fullPath))
		{
			auto& clip = m_mLoadedMusic[fullPath];
			clip->Resume();
		}
	}
	static void ResumeAll()
	{
		Mix_ResumeMusic();
		Mix_Resume(-1);
	}

	void Stop(const std::filesystem::path& file)
	{
		auto fullPath = (m_AssetPath / file).string();
		if (m_mLoadedFX.contains(fullPath))
		{
			auto& clip = m_mLoadedFX[fullPath];
			clip->Stop();
		}
		if (m_mLoadedMusic.contains(fullPath))
		{
			auto& clip = m_mLoadedMusic[fullPath];
			clip->Stop();
		}
	}
	static void StopAll()
	{
		Mix_HaltMusic();
		Mix_HaltChannel(-1);
	}

private:
	struct SDLSound final : public AudioClip
	{
		SDLSound(const std::filesystem::path& path)
		{
			m_pChunk = Mix_LoadWAV(path.string().c_str());
			if (!m_pChunk)
				std::cerr << "Failed to load sound: " << Mix_GetError() << "\n";
			m_Channel = -1;
		}
		~SDLSound() override { Mix_FreeChunk(m_pChunk); }

		SDLSound(const SDLSound& other) = delete;
		SDLSound(SDLSound&& other) noexcept = delete;
		SDLSound& operator=(const SDLSound& other) = delete;
		SDLSound& operator=(SDLSound&& other) noexcept = delete;
		
		void Play(float volume, int loops)	override { Mix_VolumeChunk(m_pChunk, static_cast<int>(100 * volume)); m_Channel = Mix_PlayChannel(-1, m_pChunk, loops); }
		void Pause()						override { if (Mix_Playing(m_Channel)) Mix_Pause(m_Channel); }
		void Resume()						override { if (Mix_Paused(m_Channel)) Mix_Resume(m_Channel); }
		void Stop()							override { Mix_HaltChannel(m_Channel); m_Channel = 0; }

	private:
		Mix_Chunk* m_pChunk;
		int m_Channel;
	};
	struct SDLMusic final : public AudioClip
	{
		SDLMusic(const std::filesystem::path& path)
		{
			m_pMusic = Mix_LoadMUS(path.string().c_str());
			if (!m_pMusic)
				std::cerr << "Failed to load sound: " << Mix_GetError() << "\n";
		}
		~SDLMusic() override { Mix_FreeMusic(m_pMusic); }

		SDLMusic(const SDLMusic& other) = delete;
		SDLMusic(SDLMusic&& other) noexcept = delete;
		SDLMusic& operator=(const SDLMusic& other) = delete;
		SDLMusic& operator=(SDLMusic&& other) noexcept = delete;

		void Play(float volume, int loops)	override { Mix_VolumeMusic(static_cast<int>(100 * volume)); Mix_PlayMusic(m_pMusic, loops); }
		void Pause()						override { if (Mix_PlayingMusic()) Mix_PauseMusic(); }
		void Resume()						override { if (Mix_PausedMusic()) Mix_ResumeMusic(); }
		void Stop()							override { Mix_HaltMusic(); }

	private:
		Mix_Music* m_pMusic;
	};

	std::filesystem::path m_AssetPath;

	std::unordered_map<std::string, std::unique_ptr<SDLSound>> m_mLoadedFX;
	std::unordered_map<std::string, std::unique_ptr<SDLMusic>> m_mLoadedMusic;
};



//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::SoundSystem::SoundSystem(const std::filesystem::path& assetPath)	{ m_pImpl = new SoundSystemImpl(assetPath); }
kob::SoundSystem::~SoundSystem()										{ delete m_pImpl; m_pImpl = nullptr; }



//--------------------------------------------------
//    Interface
//--------------------------------------------------
kob::ISoundSystem::AudioClip& 
	kob::SoundSystem::Load(const std::filesystem::path& file)							{ return m_pImpl->Load(file); }
void kob::SoundSystem::Play(const std::filesystem::path& file, float volume, int loops)	{ m_pImpl->Play(file, volume, loops); }
void kob::SoundSystem::Pause(const std::filesystem::path& file)							{ m_pImpl->Pause(file); }
void kob::SoundSystem::PauseAll()														{ SoundSystemImpl::PauseAll(); }

void kob::SoundSystem::Resume(const std::filesystem::path& file)							{ m_pImpl->Resume(file); }
void kob::SoundSystem::ResumeAll()														{ SoundSystemImpl::PauseAll(); }

void kob::SoundSystem::Stop(const std::filesystem::path& file)							{ m_pImpl->Stop(file); }
void kob::SoundSystem::StopAll()															{ SoundSystemImpl::StopAll(); }