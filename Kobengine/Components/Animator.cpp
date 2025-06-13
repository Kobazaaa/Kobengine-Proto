#include "Animator.h"
#include "Renderer.h"
#include "Timer.h"


//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::Animator::Animator(GameObject& parent, ImageRendererComponent* renderComponent, SpriteSheet* spriteSheet)
	: Component(parent)
	  , m_pRenderComponent(renderComponent)
	  , m_pSpriteSheet(spriteSheet)
	  , m_pActiveAnim(nullptr), m_IsPlaying(false), m_DoLoop(false), m_FrameTime(0), m_CurrFrame(0)
{
	m_pRenderComponent->SetSourceRect({0,0,0,0});
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::Animator::Update()
{
	if (!m_pActiveAnim)
		return;

	if (m_IsPlaying)
	{
		m_FrameTime += Timer::GetDeltaSeconds();
		if (m_FrameTime >= m_pActiveAnim->frameDelay)
		{
			++m_CurrFrame;
			m_FrameTime -= m_pActiveAnim->frameDelay;
		}

		if (m_DoLoop)
			m_CurrFrame %= static_cast<uint32_t>(m_pActiveAnim->animRects.size());
		else if (m_CurrFrame >= static_cast<uint32_t>(m_pActiveAnim->animRects.size()-1))
		{
			m_IsPlaying = false;
			m_CurrFrame = static_cast<uint32_t>(m_pActiveAnim->animRects.size() - 1);
		}
	}
	m_pRenderComponent->SetSourceRect(m_pActiveAnim->animRects[m_CurrFrame]);
}


//--------------------------------------------------
//    Setters
//--------------------------------------------------
void kob::Animator::Play(const std::string& anim, bool loop)
{
	m_IsPlaying = true;

	auto newAnim = m_pSpriteSheet->GetAnimation(anim);
	if (!newAnim || m_pActiveAnim == newAnim)
		return;
	m_FrameTime = 0;
	m_DoLoop = loop;
	m_pActiveAnim = m_pSpriteSheet->GetAnimation(anim);
}
void kob::Animator::Stop(uint32_t freezeFrame)
{
	m_IsPlaying = false;
	m_FrameTime = 0;
	m_CurrFrame = freezeFrame;
}
