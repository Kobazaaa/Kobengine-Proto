#pragma once
#include <filesystem>
#include "vec2.hpp"
#include <SDL.h>

namespace kob
{
	class Kobengine final
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Kobengine();
		~Kobengine();

		Kobengine(const Kobengine& other) = delete;
		Kobengine(Kobengine&& other) = delete;
		Kobengine& operator=(const Kobengine& other) = delete;
		Kobengine& operator=(Kobengine&& other) = delete;

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Setup();
		void Run();
		void RunOneFrame();

		//--------------------------------------------------
		//    Window
		//--------------------------------------------------
		static glm::ivec2 GetWindowSize();
		static void SetWindowSize(int width, int height);
		static void SetWindowTitle(const std::string& title);

	private:
		static std::filesystem::path FindAssetsFolder(const std::string& name);
		static void LogSDLVersion(const std::string& message, const SDL_version& v);
		static void PrintSDLVersion();

		bool m_Quit{};
		inline static SDL_Window* m_pWindow{};
	};
}
