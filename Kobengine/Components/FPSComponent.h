#pragma once
#include "Component.h"

namespace kob
{
	class TextRendererComponent;

	class FPSComponent : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit FPSComponent(GameObject& parent);


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Start() override;
		void Update() override;


		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		float GetFPS() const;


	private:
		float m_FPS{};
		TextRendererComponent* m_TextRenderer{};
	};
}
