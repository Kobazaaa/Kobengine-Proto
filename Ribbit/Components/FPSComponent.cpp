#include "FPSComponent.h"

#include "GameObject.h"
#include "TextRendererComponent.h"
#include "Timer.h"


//--------------------------------------------------
//    Constructor
//--------------------------------------------------
rib::FPSComponent::FPSComponent(GameObject& parent)
	: Component(parent)
{
}



//--------------------------------------------------
//    Loop
//--------------------------------------------------
void rib::FPSComponent::Start()
{
	m_TextRenderer = GetParent()->GetComponent<TextRendererComponent>();
}
void rib::FPSComponent::Update()
{
	m_FPS = 1.0f / Timer::GetDeltaSeconds();

	if (m_TextRenderer)
	{
		constexpr int fpsPrecision = 2;
		const int fpsInt = static_cast<int>(m_FPS);
		const int fpsDec = static_cast<int>((m_FPS - std::floor(m_FPS)) * std::pow(10, fpsPrecision));
		m_TextRenderer->SetText(std::to_string(fpsInt) + "." + std::to_string(fpsDec) + " FPS");
	}
}


//--------------------------------------------------
//    Accessors
//--------------------------------------------------
float rib::FPSComponent::GetFPS() const
{
	return m_FPS;
}
