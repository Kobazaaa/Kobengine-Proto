#include "GridRendererComponent.h"
#include "GameObject.h"
#include "Renderer.h"


//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::GridRendererComponent::GridRendererComponent(GameObject& parent, const glm::vec2& size, uint32_t rows, uint32_t cols, const glm::vec4& color)
	: Component(parent)
	, m_Size(size)
	, m_RowCol(rows, cols)
	, m_Color(color)
{}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::GridRendererComponent::Update() {}
void kob::GridRendererComponent::Render() const
{
	for (uint32_t rowIdx{}; rowIdx < m_RowCol.x; ++rowIdx)
	{
		for (uint32_t colIdx{}; colIdx < m_RowCol.y; ++colIdx)
		{
			float cellH = m_Size.y / static_cast<float>(m_RowCol.x);
			float cellW = m_Size.x / static_cast<float>(m_RowCol.y);
			Renderer::GetInstance().RenderLine({ static_cast<float>(colIdx + 1) * cellW, 0.f }, { static_cast<float>(colIdx + 1) * cellW, m_Size.y }, m_Color);
			Renderer::GetInstance().RenderLine({ 0.f, static_cast<float>(rowIdx + 1) * cellH }, { m_Size.x, static_cast<float>(rowIdx + 1) * cellH }, m_Color);
		}
	}
}
