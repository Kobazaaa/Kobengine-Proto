#pragma once
#include "NullSoundSystem.h"
#include "NullCollisionSystem.h"
#include "ISoundSystem.h"
#include "ICollisionSystem.h"

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
		static ICollisionSystem& GetCollisionService() { return *m_pCollisionService; }
		static void RegisterCollisionService(std::unique_ptr<ICollisionSystem>&& service) { m_pCollisionService = std::move(service); }

	private:
		inline static std::unique_ptr<ISoundSystem> m_pSoundService { std::make_unique<NullSoundSystem>() };
		inline static std::unique_ptr<ICollisionSystem> m_pCollisionService { std::make_unique<NullCollisionSystem>() };
	};
}