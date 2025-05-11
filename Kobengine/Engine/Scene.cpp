#include "Scene.h"
#include <algorithm>
#include <ranges>

using namespace kob;


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
Scene::Scene(const std::string& name)
	: m_Name(name)
{}


//--------------------------------------------------
//    Adding & Removing GameObjects
//--------------------------------------------------
GameObject& Scene::MoveGameObject(std::unique_ptr<GameObject> object)
{
	m_vPendingObjects.emplace_back(std::move(object));
	m_vPendingObjects.back()->OnSceneTransfer(*this);
	return *m_vPendingObjects.back();
}
GameObject& Scene::AddEmpty(const std::string& name)
{
	m_vPendingObjects.emplace_back(std::make_unique<GameObject>(*this, name));
	return *m_vPendingObjects.back();
}
void Scene::Remove(const std::unique_ptr<GameObject>& object)
{
	object->FlagForDeletion();
}
void Scene::RemoveAll()
{
	for (auto& object : m_vObjects)
	{
		object->FlagForDeletion();
	}
}

void Scene::TransferIndependent(Scene* dst)
{
	if (!dst || this == dst)
		return;

	for (auto& go : m_vObjects)
		if (go->IsSceneIndependent())
		{
			go->OnSceneTransfer(*dst);
			dst->MoveGameObject(std::move(go));
		}

	std::erase(m_vObjects, std::unique_ptr<GameObject>{});
}

void Scene::CleanupDeletedObjects()
{
	m_vObjects.erase(
		std::remove_if(m_vObjects.begin(), m_vObjects.end(),
			[](const std::unique_ptr<GameObject>& object)
			{
				return object->IsFlaggedForDeletion();
			}),
		m_vObjects.end());
}
void Scene::AddPendingObjects()
{
	for (auto& object : m_vPendingObjects)
	{
		object->Start();
		m_vObjects.push_back(std::move(object));
	}
	m_vPendingObjects.clear();
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void Scene::Start() const
{
	for(auto& object : m_vObjects)
	{
		object->Start();
	}
}
void Scene::Update() const
{
	for(auto& object : m_vObjects)
	{
		if (!object->IsActive())
			continue;
		object->Update();
	}
}
void Scene::LateUpdate()
{
	for(auto& object : m_vObjects)
	{
		if (!object->IsActive())
			continue;
		object->LateUpdate();
	}
	CleanupDeletedObjects();
	AddPendingObjects();
}
void Scene::FixedUpdate() const
{
	for(auto& object : m_vObjects)
	{
		if (!object->IsActive())
			continue;
		object->FixedUpdate();
	}
}
void Scene::Render() const
{
	for (const auto& object : m_vObjects)
	{
		if (!object->IsActive())
			continue;
		object->Render();
	}
}
void Scene::ImGuiRenderUpdate() const
{
	for (const auto& object : m_vObjects)
	{
		if (!object->IsActive())
			continue;
		object->ImGuiRenderUpdate();
	}
}

//--------------------------------------------------
//    Accessors
//--------------------------------------------------
const std::string& Scene::GetName() const
{
	return m_Name;
}
std::vector<GameObject*> Scene::GetObjectsByName(const std::string& name) const
{
	std::vector<GameObject*> result;
	for (auto& go : m_vObjects)
	{
		if (go->GetName() == name)
			result.push_back(go.get());
	}
	return result;
}
