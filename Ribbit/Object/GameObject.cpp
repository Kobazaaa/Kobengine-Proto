#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void rib::GameObject::Update()
{
	for (auto& component : m_vComponents)
	{
		component->Update();
	}

	CleanupDeletedComponents();
}
void rib::GameObject::FixedUpdate()
{
	for (auto& component : m_vComponents)
	{
		component->FixedUpdate();
	}
}
void rib::GameObject::Render() const
{
	for (auto& component : m_vComponents)
	{
		component->Render();
	}
}



//--------------------------------------------------
//    Transform
//--------------------------------------------------
rib::Transform rib::GameObject::GetTransform() const
{
	return m_transform;
}
void rib::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}


//--------------------------------------------------
//    Deletion
//--------------------------------------------------
bool rib::GameObject::IsFlaggedForDeletion() const
{
	return m_DeletionFlag;
}
void rib::GameObject::FlagForDeletion()
{
	m_DeletionFlag = true;
}



void rib::GameObject::CleanupDeletedComponents()
{
	m_vComponents.erase(
		std::remove_if(m_vComponents.begin(), m_vComponents.end(),
			[](const std::shared_ptr<Component>& component)
			{
				return component->IsFlaggedForDeletion();
			}),
		m_vComponents.end());
}
