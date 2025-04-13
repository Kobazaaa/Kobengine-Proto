#include "SDL_mixer.h"
#include "SDLSoundSystem.h"
#include <iostream>

//--------------------------------------------------
//    PIMPL
//--------------------------------------------------
class kob::SDLSoundSystem::SDLSoundSystemImpl final
{
public:
	//--------------------------------------------------
	//    Constructor & Destructor
	//--------------------------------------------------
	SDLSoundSystemImpl() = default;

	//--------------------------------------------------
	//    Functions
	//--------------------------------------------------
	void Play()
	{
		std::cout << "Play";
	}

private:

};



//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::SDLSoundSystem::SDLSoundSystem()	{ m_pImpl = new SDLSoundSystemImpl(); }
kob::SDLSoundSystem::~SDLSoundSystem()	{ delete m_pImpl; m_pImpl = nullptr; }

//--------------------------------------------------
//    Interface
//--------------------------------------------------
void kob::SDLSoundSystem::Play()		{ m_pImpl->Play(); }
