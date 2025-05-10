#pragma once
#include "Component.h"
#include "ImageRendererComponent.h"
#include "SpriteSheet.h"

namespace kob
{
	class Animator : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		Animator(GameObject& parent, ImageRendererComponent* renderComponent, SpriteSheet* spriteSheet);


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;


		//--------------------------------------------------
		//    Setters
		//--------------------------------------------------
		void Play(const std::string& anim, bool loop);
		void Stop(uint32_t freezeFrame = 0);

	private:
		ImageRendererComponent* m_pRenderComponent;
		SpriteSheet* m_pSpriteSheet;
		SpriteSheetAnimation* m_pActiveAnim;
		bool m_IsPlaying;
		bool m_DoLoop;
		float m_FrameTime;
		uint32_t m_CurrFrame;
	};
}
