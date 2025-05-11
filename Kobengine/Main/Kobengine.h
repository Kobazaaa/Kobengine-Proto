#pragma once
#include <filesystem>
#include "vec2.hpp"

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
		glm::ivec2 GetWindowSize() const;
		void SetWindowSize(int width, int height) const;
		void SetWindowTitle(const std::string& title) const;

	private:
		static std::filesystem::path FindAssetsFolder(const std::string& name);
		static void LogSDLVersion(const std::string& message, const SDL_version& v);
		static void PrintSDLVersion();

		bool m_Quit{};
		SDL_Window* m_pWindow{};
	};
}
