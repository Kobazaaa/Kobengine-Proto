#pragma once
#include <string>
#include <functional>
#include <filesystem>

namespace kob
{
	class Kobengine final
	{
		bool m_quit{};
	public:
		explicit Kobengine(const std::filesystem::path& dataPath);
		~Kobengine();
		void Run(const std::function<void()>& load);
		void RunOneFrame();

		Kobengine(const Kobengine& other) = delete;
		Kobengine(Kobengine&& other) = delete;
		Kobengine& operator=(const Kobengine& other) = delete;
		Kobengine& operator=(Kobengine&& other) = delete;
	};
}