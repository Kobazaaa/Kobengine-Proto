#pragma once
#include <functional>
#include <filesystem>

namespace kob
{
	class Kobengine final
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Kobengine(const std::filesystem::path& dataPath);
		~Kobengine();

		Kobengine(const Kobengine& other) = delete;
		Kobengine(Kobengine&& other) = delete;
		Kobengine& operator=(const Kobengine& other) = delete;
		Kobengine& operator=(Kobengine&& other) = delete;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Run(const std::function<void()>& load);
		void RunOneFrame();

	private:
		static void LogSDLVersion(const std::string& message, const SDL_version& v);
		static void PrintSDLVersion();

		bool m_Quit{};
		SDL_Window* m_pWindow{};
	};
}