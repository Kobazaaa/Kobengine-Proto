#pragma once
namespace kob
{
	template <typename T>
	class Singleton
	{
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
	protected:
		Singleton() = default;
	public:
		virtual ~Singleton() = default;
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;


		//--------------------------------------------------
		//    Accessor
		//--------------------------------------------------
		static T& GetInstance()
		{
			static T instance{};
			return instance;
		}
	};
}