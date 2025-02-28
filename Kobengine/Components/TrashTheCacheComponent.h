#pragma once

#include "Component.h"

namespace kob
{
	class TrashTheCacheComponent : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit TrashTheCacheComponent(GameObject& parent);


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Start() override;
		void Update() override;
		void ImGuiRenderUpdate() override;

	private:
	};

}
