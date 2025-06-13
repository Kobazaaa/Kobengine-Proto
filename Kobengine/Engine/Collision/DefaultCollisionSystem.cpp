// Kobengine
#include "DefaultCollisionSystem.h"
#include "ColliderComponent.h"
#include "GameObject.h"

//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::DefaultCollisionSystem::~DefaultCollisionSystem()
{
	m_vRegisteredColliders.clear();
}

//--------------------------------------------------
//    Interface
//--------------------------------------------------
void kob::DefaultCollisionSystem::RegisterCollider(ColliderComponent& component)
{
	m_vRegisteredColliders.push_back(&component);
}
void kob::DefaultCollisionSystem::UnregisterCollider(ColliderComponent& component)
{
	erase_if(m_vRegisteredColliders, [&component](const Component* registered) {return &component == registered; });
}
void kob::DefaultCollisionSystem::EvaluateCollisions()
{
	// Reset
	m_vCurrentCollisions.clear();

	// Handle Enter / Stay Collisions
	const uint32_t collCount = static_cast<uint32_t>(m_vRegisteredColliders.size());
	for (uint32_t i{}; i < collCount; ++i)
	{
		const auto coll1 = m_vRegisteredColliders[i];
		const auto obj1 = coll1->GetGameObject();
		for (uint32_t j{}; j < collCount; ++j)
		{
			const auto coll2 = m_vRegisteredColliders[j];
			const auto obj2 = coll2->GetGameObject();
			CollisionPair pair = { .first = obj1, .second = obj2 };
			if (coll1 == coll2 || m_vCurrentCollisions.contains(pair))
				continue;

			// do the two colliders collide?
			if (coll1->Overlaps(*coll2))
			{
				m_vCurrentCollisions.insert(pair);
				// Is the collision new this frame?
				if (!m_vPreviousCollisions.contains(pair))
				{
					// trigger new collision
					if (!obj1->IsFlaggedForDeletion()) obj1->OnCollisionEnter(*obj2);
					if (!obj2->IsFlaggedForDeletion()) obj2->OnCollisionEnter(*obj1);
				}
				else
				{
					// trigger existing collision
					if (!obj1->IsFlaggedForDeletion()) obj1->OnCollisionStay(*obj2);
					if (!obj2->IsFlaggedForDeletion()) obj2->OnCollisionStay(*obj1);
				}
			}
		}
	}

	// Handle Exit Collisions
	for (const auto& pair : m_vPreviousCollisions)
	{
		if (!m_vCurrentCollisions.contains(pair))
		{
			if (!pair.first->IsFlaggedForDeletion()) pair.first->OnCollisionExit(*pair.second);
			if (!pair.second->IsFlaggedForDeletion()) pair.second->OnCollisionExit(*pair.first);
		}
	}

	// Swap data for next frame
	std::swap(m_vPreviousCollisions, m_vCurrentCollisions);
}
