#include "ColliderComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::ColliderComponent::ColliderComponent(GameObject& parent)
	: Component(parent)
{
	ServiceLocator::GetCollisionService().RegisterCollider(*this);
}
kob::ColliderComponent::~ColliderComponent()
{
    ServiceLocator::GetCollisionService().UnregisterCollider(*this);
}


//--------------------------------------------------
//    Helpers
//--------------------------------------------------
void kob::ColliderComponent::Update() { }
bool kob::ColliderComponent::Contains(const glm::vec3& point) const
{
	const auto pos = GetGameObject()->GetWorldTransform().GetPosition() + offset;
    const auto halfSize = GetSize() / 2.f;
    return  point.x >= pos.x - halfSize.x &&
            point.x <= pos.x + halfSize.x &&
            point.y >= pos.y - halfSize.y &&
            point.y <= pos.y + halfSize.y &&
            point.z >= pos.z - halfSize.z &&
            point.z <= pos.z + halfSize.z;
}
bool kob::ColliderComponent::Overlaps(const ColliderComponent& coll) const
{
    const auto pos = GetGameObject()->GetWorldTransform().GetPosition() + offset;
    const auto halfSize = GetSize() / 2.f;
    const auto oPos = coll.GetGameObject()->GetWorldTransform().GetPosition() + coll.offset;
    const auto oHalfSize = coll.GetSize() / 2.f;

    return  (pos.x - halfSize.x <= oPos.x + oHalfSize.x && pos.x + halfSize.x >= oPos.x - oHalfSize.x) &&
	        (pos.y - halfSize.y <= oPos.y + oHalfSize.y && pos.y + halfSize.y >= oPos.y - oHalfSize.y) &&
	        (pos.z - halfSize.z <= oPos.z + oHalfSize.z && pos.z + halfSize.z >= oPos.z - oHalfSize.z);
}

//--------------------------------------------------
//    Accessors & Mutators
//--------------------------------------------------
glm::vec3 kob::ColliderComponent::GetSize() const { return m_Size * GetGameObject()->GetWorldTransform().GetScale(); }
void kob::ColliderComponent::SetSize(const glm::vec3& size) { m_Size.x = abs(size.x); m_Size.y = abs(size.y); }
