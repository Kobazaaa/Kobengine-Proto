#pragma once
#include <unordered_set>
#include <vector>
#include "ICollisionSystem.h"

namespace kob
{

	class DefaultCollisionSystem final : public ICollisionSystem
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		DefaultCollisionSystem() = default;
		~DefaultCollisionSystem() override;

		DefaultCollisionSystem(const DefaultCollisionSystem& other) = delete;
		DefaultCollisionSystem(DefaultCollisionSystem&& other) noexcept = delete;
		DefaultCollisionSystem& operator=(const DefaultCollisionSystem& other) = delete;
		DefaultCollisionSystem& operator=(DefaultCollisionSystem&& other) noexcept = delete;

		//--------------------------------------------------
		//    Interface
		//--------------------------------------------------
		void RegisterCollider(ColliderComponent& component) override;
		void UnregisterCollider(ColliderComponent& component) override;
		void EvaluateCollisions() override;

	private:
		struct CollisionPair
		{
			GameObject* first;
			GameObject* second;
			bool operator==(const CollisionPair& other) const
			{
				return (first == other.first && second == other.second) || (first == other.second && second == other.first);
			}
		};
		struct CollisionPairHash
		{
			std::size_t operator()(const CollisionPair& pair) const
			{
				const auto h1 = std::hash<GameObject*>{}(pair.first);
				const auto h2 = std::hash<GameObject*>{}(pair.second);
				return h1 ^ h2; // pair A, B is the same as pair B, A, using ^ will result in the same hash
			}
		};
		std::unordered_set<CollisionPair, CollisionPairHash> m_vPreviousCollisions;
		std::unordered_set<CollisionPair, CollisionPairHash> m_vCurrentCollisions;
		std::vector<ColliderComponent*> m_vRegisteredColliders;
	};
}
