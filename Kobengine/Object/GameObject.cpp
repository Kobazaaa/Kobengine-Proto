#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Scene.h"


//--------------------------------------------------
//    Constructors and Destructors
//--------------------------------------------------
kob::GameObject::GameObject(Scene& scene, const std::string& name)
	: m_pScene(&scene)
	, name(name)
{}

//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::GameObject::Start()
{
	for (const auto& component : m_vComponents)
		component->Start();
}
void kob::GameObject::Update()
{
	for (const auto& component : m_vComponents)
		component->Update();
}
void kob::GameObject::LateUpdate()
{
	for (const auto& component : m_vComponents)
		component->LateUpdate();
	CleanupDeletedComponents();
}
void kob::GameObject::FixedUpdate()
{
	for (const auto& component : m_vComponents)
		component->FixedUpdate();
}
void kob::GameObject::Render() const
{
	for (const auto& component : m_vComponents)
		component->Render();
}
void kob::GameObject::ImGuiRenderUpdate()
{
	for (const auto& component : m_vComponents)
		component->ImGuiRenderUpdate();
}

void kob::GameObject::OnCollisionEnter(GameObject& other)
{
	for (const auto& component : m_vComponents)
		component->OnCollisionEnter(other);
}
void kob::GameObject::OnCollisionExit(GameObject& other)
{
	for (const auto& component : m_vComponents)
		component->OnCollisionExit(other);
}
void kob::GameObject::OnCollisionStay(GameObject& other)
{
	for (const auto& component : m_vComponents)
		component->OnCollisionStay(other);
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
		{
			SetLocalPosition(GetWorldTransform().GetPosition() - parent->GetWorldTransform().GetPosition());
			SetLocalScale(GetWorldTransform().GetScale() / parent->GetWorldTransform().GetScale());
			SetLocalRotation(GetWorldTransform().GetEulerRotation() - parent->GetWorldTransform().GetEulerRotation());
		}
		SetTransformDirty();
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
	if (m_DirtyTransformFlag)
		UpdateWorldPosition();
	return m_WorldTransform;
}

void kob::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalTransform.SetPosition(pos.x, pos.y, pos.z);
	SetTransformDirty();
}

void kob::GameObject::SetLocalScale(const glm::vec3& scale)
{
	m_LocalTransform.SetScale(scale.x, scale.y, scale.z);
	SetTransformDirty();
}

void kob::GameObject::SetLocalRotation(const glm::vec3& eulerAngles)
{
	m_LocalTransform.SetEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	SetTransformDirty();
}

void kob::GameObject::UpdateWorldPosition()
{
	if (m_DirtyTransformFlag)
	{
		if (m_pParent == nullptr)
			m_WorldTransform = m_LocalTransform;
		else
		{
			const auto newPos = m_pParent->GetWorldTransform().GetPosition() + m_LocalTransform.GetPosition();
			m_WorldTransform.SetPosition(newPos);

			const auto newScale = m_pParent->GetWorldTransform().GetScale() * m_LocalTransform.GetScale();
			m_WorldTransform.SetScale(newScale);

			const auto newRot = m_pParent->GetWorldTransform().GetEulerRotation() + m_LocalTransform.GetEulerRotation();
			m_WorldTransform.SetEulerAngles(newRot);
		}
	}
	m_DirtyTransformFlag = false;
}


//--------------------------------------------------
//    Data
//--------------------------------------------------
void kob::GameObject::SetRenderPriority(int newPriority)
{
	if (newPriority != m_RenderPriority)
	{
		m_RenderPriority = newPriority;
		m_pScene->MarkRenderOrderDirty();
	}
}
int kob::GameObject::GetRenderPriority() const { return m_RenderPriority; }
bool kob::GameObject::CompareTag(const std::string& oTag) const
{
	// todo ew, what is this? No string comparison please :D
	return oTag == tag;
}
kob::Scene& kob::GameObject::GetScene()	const	{ return *m_pScene; }


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
	for (const auto& child : m_vChildren)
		child->FlagForDeletion();
}

void kob::GameObject::FlagSceneIndependent()
{
	m_SceneIndependent = true;
	for (const auto& child : m_vChildren)
		child->FlagSceneIndependent();
}
bool kob::GameObject::IsSceneIndependent() const { return m_SceneIndependent; }

void kob::GameObject::SetTransformDirty()
{
	m_DirtyTransformFlag = true;
	for (const auto& child : m_vChildren)
		child->SetTransformDirty();
}

bool kob::GameObject::IsActive()				const	{ return m_IsActive; }
void kob::GameObject::SetActive(bool active)
{
	m_IsActive = active;
	for (auto& child : m_vChildren)
		child->SetActive(active);
}

void kob::GameObject::OnSceneTransfer(Scene& scene)
{
	m_pScene = &scene;
	for (auto& child : m_vChildren)
		child->OnSceneTransfer(scene);
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
	if (std::find(m_vChildren.begin(), m_vChildren.end(), child) != m_vChildren.end())
		return;

	m_vChildren.push_back(child);
}
void kob::GameObject::RemoveChild(const GameObject* child)
{
	std::erase_if(m_vChildren, [&](const GameObject* pChild)
								    {
								        return pChild == child;
								    });
}
