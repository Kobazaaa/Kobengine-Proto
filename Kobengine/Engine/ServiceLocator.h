#pragma once
#include "ISoundSystem.h"

namespace kob
{
	template<typename ServiceType>
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
		//    Accessors & Mutators
		//--------------------------------------------------
		static ServiceType& GetService() { return *m_pService; }
		static void RegisterService(std::unique_ptr<ServiceType>&& service) { m_pService = std::move(service); }

	private:
		inline static std::unique_ptr<ServiceType> m_pService { nullptr };
	};
}