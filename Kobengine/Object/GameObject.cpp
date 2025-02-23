#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"



//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::GameObject::Start()
{
	for (auto& component : m_vComponents)
	{
		component->Start();
	}
}

void kob::GameObject::Update()
{
	for (auto& component : m_vComponents)
	{
		component->Update();
	}
}

void kob::GameObject::LateUpdate()
{
	for (auto& component : m_vComponents)
	{
		component->LateUpdate();
	}

	CleanupDeletedComponents();
}

void kob::GameObject::FixedUpdate()
{
	for (auto& component : m_vComponents)
	{
		component->FixedUpdate();
	}
}
void kob::GameObject::Render() const
{
	for (auto& component : m_vComponents)
	{
		component->Render();
	}
}


//--------------------------------------------------
//    Parent-Child
//--------------------------------------------------
kob::GameObject* kob::GameObject::GetParent() const
{
	return m_pParent;
}
void kob::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
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
bool kob::GameObject::IsChild(const GameObject* child) const
{
	return std::find(m_vChildren.begin(), m_vChildren.end(), child) != m_vChildren.end();
}
int kob::GameObject::GetChildCount() const
{
	return static_cast<int>(m_vChildren.size());
}
kob::GameObject* kob::GameObject::GetChildAt(int index) const
{
	if (index < 0 || index >= GetChildCount()) return nullptr;
	return m_vChildren[index];
}
const std::vector<kob::GameObject*>& kob::GameObject::GetAllChildren() const
{
	return m_vChildren;
}

//--------------------------------------------------
//    Transform
//--------------------------------------------------
const kob::Transform& kob::GameObject::GetLocalTransform() const
{
	return m_LocalTransform;
}
const kob::Transform& kob::GameObject::GetWorldTransform()
{
	if (m_DirtyPositionFlag)
		UpdateWorldPosition();
	return m_WorldTransform;
}

void kob::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalTransform.SetPosition(pos.x, pos.y, pos.z);
	SetPositionDirty();
}
void kob::GameObject::UpdateWorldPosition()
{
	//TODO fix transform to work properly so I can work with more than just position (scale/rotation)
	if (m_DirtyPositionFlag)
	{
		if (m_pParent == nullptr)
			m_WorldTransform = m_LocalTransform;
		else
		{
			const auto newPos = m_pParent->GetWorldTransform().GetPosition() + m_LocalTransform.GetPosition();
			m_WorldTransform.SetPosition(newPos);
		}
	}
	m_DirtyPositionFlag = false;
}


//--------------------------------------------------
//    Deletion
//--------------------------------------------------
bool kob::GameObject::IsFlaggedForDeletion() const
{
	return m_DeletionFlag;
}
void kob::GameObject::FlagForDeletion()
{
	m_DeletionFlag = true;
}
void kob::GameObject::SetPositionDirty()
{
	m_DirtyPositionFlag = true;
	for (auto& child : m_vChildren)
		child->SetPositionDirty();
}


void kob::GameObject::CleanupDeletedComponents()
{
	m_vComponents.erase(
		std::remove_if(m_vComponents.begin(), m_vComponents.end(),
			[](const std::unique_ptr<Component>& component)
			{
				return component->IsFlaggedForDeletion();
			}),
		m_vComponents.end());
}


void kob::GameObject::AddChild(GameObject* child)
{
	// If the child already exists in the container, don't add it again!
	if (std::find(m_vChildren.begin(), m_vChildren.end(), child) == m_vChildren.end())
		return;

	m_vChildren.push_back(child);
}
void kob::GameObject::RemoveChild(GameObject* child)
{
	std::erase_if(m_vChildren, [&](const GameObject* pChild)
								    {
								        return pChild == child;
								    });
}
