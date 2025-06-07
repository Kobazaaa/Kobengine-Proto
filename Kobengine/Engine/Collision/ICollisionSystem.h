#pragma once
namespace kob
{
	class GameObject;
	class ColliderComponent;
	class ICollisionSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		virtual ~ICollisionSystem() = default;

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		virtual void RegisterCollider(ColliderComponent& component) = 0;
		virtual void UnregisterCollider(ColliderComponent& component) = 0;
		virtual void EvaluateCollisions() = 0;
	};
}
