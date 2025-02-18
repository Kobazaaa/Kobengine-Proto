#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"



//--------------------------------------------------
//    Loop
//--------------------------------------------------
void rib::GameObject::Start()
{
	for (auto& component : m_vComponents)
	{
		component->Start();
	}
}

void rib::GameObject::Update()
{
	for (auto& component : m_vComponents)
	{
		component->Update();
	}
}

void rib::GameObject::LateUpdate()
{
	for (auto& component : m_vComponents)
	{
		component->LateUpdate();
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
//    Parent-Child
//--------------------------------------------------
rib::GameObject* rib::GameObject::GetParent() const
{
	return m_pParent;
}
void rib::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_pParent == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldTransform().GetPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldTransform().GetPosition() - parent->GetWorldTransform().GetPosition());
		SetPositionDirty();
	}
	if (m_pParent) m_pParent->RemoveChild(this);
	m_pParent = parent;
	if (m_pParent) m_pParent->AddChild(this);
}
bool rib::GameObject::IsChild(const GameObject* child) const
{
	return std::find(m_vChildren.begin(), m_vChildren.end(), child) != m_vChildren.end();
}
int rib::GameObject::GetChildCount() const
{
	return static_cast<int>(m_vChildren.size());
}
rib::GameObject* rib::GameObject::GetChildAt(int index) const
{
	if (index < 0 || index >= GetChildCount()) return nullptr;
	return m_vChildren[index];
}

//--------------------------------------------------
//    Transform
//--------------------------------------------------
rib::Transform rib::GameObject::GetLocalTransform() const
{
	return m_LocalTransform;
}
rib::Transform rib::GameObject::GetWorldTransform()
{
	if (m_DirtyPositionFlag)
		UpdateWorldPosition();
	return m_WorldTransform;
}

void rib::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalTransform.SetPosition(pos.x, pos.y, pos.z);
	SetPositionDirty();
}
void rib::GameObject::UpdateWorldPosition()
{
	//TODO fix transform to work properly so I can work with more then just pos
	if (m_DirtyPositionFlag)
	{
		if (m_pParent == nullptr)
			m_WorldTransform = m_LocalTransform;
		else
		{
			auto newPos = m_pParent->GetWorldTransform().GetPosition() + m_LocalTransform.GetPosition();
			m_WorldTransform.SetPosition(newPos.x, newPos.y, newPos.z);
		}
	}
	m_DirtyPositionFlag = false;
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
void rib::GameObject::SetPositionDirty()
{
	m_DirtyPositionFlag = true;
}


void rib::GameObject::CleanupDeletedComponents()
{
	m_vComponents.erase(
		std::remove_if(m_vComponents.begin(), m_vComponents.end(),
			[](const std::unique_ptr<Component>& component)
			{
				return component->IsFlaggedForDeletion();
			}),
		m_vComponents.end());
}


void rib::GameObject::AddChild(GameObject* child)
{
	m_vChildren.push_back(child);
}
void rib::GameObject::RemoveChild(GameObject* child)
{
	std::erase_if(m_vChildren, [&](const GameObject* pChild)
								    {
								        return pChild == child;
								    });
}
