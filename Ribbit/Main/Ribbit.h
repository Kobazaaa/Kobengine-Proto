#pragma once
#include <string>
#include <functional>
#include <filesystem>

namespace rib
{
	class Ribbit final
	{
		bool m_quit{};
	public:
		explicit Ribbit(const std::filesystem::path& dataPath);
		~Ribbit();
		void Run(const std::function<void()>& load);
		void RunOneFrame();

		Ribbit(const Ribbit& other) = delete;
		Ribbit(Ribbit&& other) = delete;
		Ribbit& operator=(const Ribbit& other) = delete;
		Ribbit& operator=(Ribbit&& other) = delete;
	};
}