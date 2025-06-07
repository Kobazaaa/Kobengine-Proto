#pragma once
#include "NullSoundSystem.h"
#include "ISoundSystem.h"

namespace kob
{
	class ServiceLocator final
	{
	public:
		//--------------------------------------------------
		//    Constructors and Destructors
		//--------------------------------------------------
		ServiceLocator() = delete;
		~ServiceLocator() = delete;

		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) = delete;

		//--------------------------------------------------
		//    Services
		//--------------------------------------------------
		static ISoundSystem& GetSoundService() { return *m_pSoundService; }
		static void RegisterSoundService(std::unique_ptr<ISoundSystem>&& service) { m_pSoundService = std::move(service); }

	private:
		inline static std::unique_ptr<ISoundSystem> m_pSoundService { std::make_unique<NullSoundSystem>() };
	};
}