#pragma once
#include "Component.h"
#include "vec2.hpp"
#include "vec4.hpp"

namespace kob
{
	class GridRendererComponent : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit GridRendererComponent(GameObject& parent, const glm::vec2& size, uint32_t rows, uint32_t cols, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f});


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;
		void Render() const override;

	private:
		glm::vec2 m_Size		{};
		glm::uvec2 m_RowCol		{};
		glm::vec4 m_Color		{};
	};
}
