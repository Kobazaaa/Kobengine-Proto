#include "ThrashTheCacheComponent.h"

//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::ThrashTheCacheComponent::ThrashTheCacheComponent(GameObject& parent)
	: Component(parent)
{}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::ThrashTheCacheComponent::Update() {}
void kob::ThrashTheCacheComponent::ImGuiRenderUpdate()
{
	ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2(5, 5));

	// EXERCISE 01
	ImGuiExercise01();
	// EXERCISE 02
	ImGuiExercise02();

	ImPlot::PopStyleVar();
}


//--------------------------------------------------
//    ImGui per exercise
//--------------------------------------------------
void kob::ThrashTheCacheComponent::PlotResults(const char* title, const std::vector<float>& results, const ImVec4& lineColor)
{
	if (!results.empty())
	{
		constexpr auto flags = ImPlotFlags_NoInputs | ImPlotFlags_NoTitle | ImPlotFlags_Crosshairs;
		if (ImPlot::BeginPlot(title, m_GRAPH_SIZES, flags))
		{
			ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_AutoFit,
												ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_AutoFit);

			ImPlot::PushStyleColor(ImPlotCol_Line, lineColor);
			ImPlot::PlotLine("", results.data(), static_cast<int>(results.size()));
			ImPlot::PopStyleColor();

			ImPlot::EndPlot();
		}
	}

}
void kob::ThrashTheCacheComponent::ImGuiExercise01()
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(m_WINDOW_SIZES, ImGuiCond_Once);

	ImGui::Begin("Trash The Cache: Exercise01");
	{
		// Allow user to change sample count
		ImGui::TextWrapped("Depending on the Number of Samples, computation time might take a while. Your cache is being trashed using an array with %i elements.", m_ARRAY_SIZE);
		ImGui::Spacing();
		ImGui::Text("Number of Samples to Take");
		ImGui::InputInt("# samples", &m_SampleCountEx01);
		m_SampleCountEx01 = std::max(1, m_SampleCountEx01);

		// Upon the press of a button, Trash the Cache
		if (ImGui::Button("Trash the cache"))
		{
			TrashTheCache<int>(m_SampleCountEx01, m_Exercise01Results, [&](auto& v, const int stepSize)
				{
					for (int i = 0; i < m_ARRAY_SIZE; i += stepSize)
					{
						v[i] *= 2;
					}
				});
		}
		// If measurements have been taken, plot them on a graph
		PlotResults("Exercise 01", m_Exercise01Results, ImVec4(1, 0.5f, 0, 1));
	}
	ImGui::End();
}
void kob::ThrashTheCacheComponent::ImGuiExercise02()
{
	ImGui::SetNextWindowPos(ImVec2(320, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(m_WINDOW_SIZES, ImGuiCond_Once);

	ImGui::Begin("Trash The Cache: Exercise02");
	{
		// Allow user to change sample count
		ImGui::TextWrapped("Depending on the Number of Samples, computation time might take a while. Your cache is being trashed using an array with %i elements.", m_ARRAY_SIZE);
		ImGui::Spacing();
		ImGui::Text("Number of Samples to Take");
		ImGui::InputInt("# samples", &m_SampleCountEx02);
		m_SampleCountEx02 = std::max(1, m_SampleCountEx02);

		// GameObject3D
		if (ImGui::Button("Trash the cache with GameObject3D"))
		{
			TrashTheCache<GameObject3D>(m_SampleCountEx02, m_Exercise02Results, [&](auto& v, const int stepSize)
				{
					for (int i = 0; i < m_ARRAY_SIZE; i += stepSize)
					{
						v[i].ID *= 2;
					}
				});
		}
		PlotResults("Exercise 02", m_Exercise02Results, ImVec4(0, 1, 1, 1));

		// GameObject3D Alt
		if (ImGui::Button("Trash the cache with GameObject3D Alt"))
		{
			TrashTheCache<GameObject3DAlt>(m_SampleCountEx02, m_Exercise02AltResults, [&](auto& v, const int stepSize)
				{
					for (int i = 0; i < m_ARRAY_SIZE; i += stepSize)
					{
						v[i].ID *= 2;
					}
				});
		}
		PlotResults("Exercise 02 Alt", m_Exercise02AltResults, ImVec4(0, 1, 0, 1));

		// Combined
		if (!m_Exercise02AltResults.empty() && !m_Exercise02Results.empty())
		{
			ImGui::Text("Combined:");
			constexpr auto flags = ImPlotFlags_NoInputs | ImPlotFlags_NoTitle | ImPlotFlags_Crosshairs;
			if (ImPlot::BeginPlot("Exercise 02 Combines", m_GRAPH_SIZES, flags))
			{
				ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_AutoFit,
													ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_AutoFit);


				ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(0, 1, 1, 1));
				ImPlot::PlotLine("GameObject3D", m_Exercise02Results.data(), static_cast<int>(m_Exercise02Results.size()));
				ImPlot::PopStyleColor();

				ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(0, 1, 0, 1));
				ImPlot::PlotLine("GameObject3D Alt", m_Exercise02AltResults.data(), static_cast<int>(m_Exercise02AltResults.size()));
				ImPlot::PopStyleColor();

				ImPlot::EndPlot();
			}
		}
	}
	ImGui::End();
}
