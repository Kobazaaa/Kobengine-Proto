#include "LoggerSoundSystem.h"
#include <iostream>

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::LoggerSoundSystem::LoggerSoundSystem(std::unique_ptr<ISoundSystem>&& ss)
	: m_pRealSoundSystem(std::move(ss))
{ }


//--------------------------------------------------
//    Interface
//--------------------------------------------------
kob::ISoundSystem::AudioClip& kob::LoggerSoundSystem::Load(const std::filesystem::path& file)
{
	std::cout << "Loading " << file << "\n";
	return m_pRealSoundSystem->Load(file);
}

void kob::LoggerSoundSystem::Play(const std::filesystem::path& file, float volume, int loops)
{
	// add 1 to the loops, since loops indicates how many times extra the audio plays
	std::string loopTimes = (loops == -1 ? "forever" : std::to_string(loops + 1) + " times");
	std::cout << "Playing " << file << " at volume " << volume << " " << loopTimes << "\n";
	m_pRealSoundSystem->Play(file, volume, loops);
}

void kob::LoggerSoundSystem::Pause(const std::filesystem::path& file)
{
	std::cout << "Pausing " << file << "\n";
	m_pRealSoundSystem->Pause(file);
}
void kob::LoggerSoundSystem::PauseAll()
{
	std::cout << "Pausing all sound!\n";
	m_pRealSoundSystem->PauseAll();
}

void kob::LoggerSoundSystem::Resume(const std::filesystem::path& file)
{
	std::cout << "Resuming " << file << "\n";
	m_pRealSoundSystem->Resume(file);
}
void kob::LoggerSoundSystem::ResumeAll()
{
	std::cout << "Resuming all sound!\n";
	m_pRealSoundSystem->ResumeAll();
}

void kob::LoggerSoundSystem::Stop(const std::filesystem::path& file)
{
	std::cout << "Stopping " << file << "\n";
	m_pRealSoundSystem->Stop(file);
}
void kob::LoggerSoundSystem::StopAll()
{
	std::cout << "Stopping all sound!\n";
	m_pRealSoundSystem->StopAll();
}
void kob::LoggerSoundSystem::SetGlobalVolumeScale(float scale)
{
	std::cout << "New global volume scale: " << scale << "\n";
	m_pRealSoundSystem->SetGlobalVolumeScale(scale);
}
float kob::LoggerSoundSystem::GetGlobalVolumeScale() { return m_pRealSoundSystem->GetGlobalVolumeScale(); }
