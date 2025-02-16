#pragma once
#include "Component.h"

namespace rib
{
	class FPSComponent : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit FPSComponent(GameObject* parent);


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;
		void Render() const override;


		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		float GetFPS() const;


	private:
		float m_FPS{};
	};
}
