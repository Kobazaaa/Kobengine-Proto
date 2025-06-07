#pragma once
#include "ICollisionSystem.h"

namespace kob
{
	class NullCollisionSystem final : public ICollisionSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		NullCollisionSystem() = default;

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		void RegisterCollider(ColliderComponent&) override {}
		void UnregisterCollider(ColliderComponent&) override {}
		void EvaluateCollisions() override {}
	};
}
