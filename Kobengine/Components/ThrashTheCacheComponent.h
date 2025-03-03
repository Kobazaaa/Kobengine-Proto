#pragma once

#include <algorithm>

#include "Component.h"
#include <chrono>
#include <vector>
#include <numeric>
#include <functional>

namespace kob
{
	class ThrashTheCacheComponent : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit ThrashTheCacheComponent(GameObject& parent);


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;
		void ImGuiRenderUpdate() override;

	private:

		// Data Structs
		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };
		};
		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};
		class GameObject3DAlt
		{
		public:
			Transform* transform;
			int ID;
		};

		// ImGui per exercise
		void PlotResults(const char* title, const std::vector<float>& results, const ImVec4& lineColor);
		void ImGuiExercise01();
		void ImGuiExercise02();

		// Timings
		template <typename T, typename Func>
		void TrashTheCache(const int sampleCount, std::vector<float>& results, Func func)
		{
			// Create a vector to store the measurements per step size
			std::vector<float> measurements(sampleCount);

			// Create a big array of data
			std::vector<T> dataArray(m_ARRAY_SIZE);

			results.clear();
			results.resize(static_cast<int>(std::log2(m_MAX_STEP_SIZE)) + 1);

			// Measure [sampleCount] number of times
			int resultIdx = 0;
			for (int stepSize = 1; stepSize <= m_MAX_STEP_SIZE; stepSize *= 2)
			{
				for (int sampleIdx = 0; sampleIdx < sampleCount; ++sampleIdx)
				{
					// Measure deltaMicroseconds
					auto startTime = std::chrono::high_resolution_clock::now();

					func(dataArray, stepSize);

					auto endTime = std::chrono::high_resolution_clock::now();
					const auto elapsedMicroSeconds = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
					measurements[sampleIdx] = static_cast<float>(elapsedMicroSeconds);
				}

				// Sort the measurements ascending
				std::ranges::sort(measurements);

				// Calculate how many outliers to discard
				const int discardPercent = static_cast<int>(sampleCount * 0.2f); // Remove 20% of sample count as outliers
				const int nrOfOutliersToRemove = discardPercent % 2 == 0 ? discardPercent : discardPercent - 1; // ensure the nr of outliers to remove is always even
				const int oneSidedOutliers = nrOfOutliersToRemove / 2;

				// Discard outliers
				auto average = std::accumulate(measurements.begin() + oneSidedOutliers, measurements.end() - oneSidedOutliers, 0.f);
				average /= (sampleCount - nrOfOutliersToRemove);

				results[resultIdx] = average;
				++resultIdx;
			}
		}

		// Data members
        const int m_ARRAY_SIZE = static_cast<int>(std::pow(2, 25));
        const int m_MAX_STEP_SIZE = 1024;
		const ImVec2 m_GRAPH_SIZES{ 290, 150 };
		const ImVec2 m_WINDOW_SIZES{ 300, 400 };

		// Sample Counts
        int m_SampleCountEx01 = 10;
        int m_SampleCountEx02 = 10;

		// Timing Results
        std::vector<float> m_Exercise01Results;
        std::vector<float> m_Exercise02Results;
        std::vector<float> m_Exercise02AltResults;
	};
}
