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
	const auto count = std::erase_if(m_vObjects,
	              [](const std::unique_ptr<GameObject>& object)
	              {
		              return object->IsFlaggedForDeletion();
	              });

	if (count > 0)
		m_DirtyRenderOrder = true;
}
void Scene::SortOnRenderPriority()
{
	if (!m_DirtyRenderOrder)
		return;
	std::ranges::sort(m_vObjects, [](const auto& go1, const auto& go2)
		{
			return go1->GetRenderPriority() > go2->GetRenderPriority();
		});
	m_DirtyRenderOrder = false;
}
void Scene::AddPendingObjects()
{
	// separate for loops to ensure that all objects in m_vPendingObjects are in a valid state, since it's possible to query
	// m_vPendingObjects in the start function of GameObjects (e.g. asking for all GO with tag or name).
	for (auto& object : m_vPendingObjects)
		object->Start();
	for (auto& object : m_vPendingObjects)
		m_vObjects.push_back(std::move(object));
	if (!m_vPendingObjects.empty())
		m_DirtyRenderOrder = true;
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
	SortOnRenderPriority();
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
		if (go->name == name) //todo booo, string comparison, boooo!!!
			result.push_back(go.get());
	}
	for (auto& go : m_vPendingObjects)
	{
		if (go->name == name) //todo booo, string comparison, boooo!!!
			result.push_back(go.get());
	}
	return result;
}
std::vector<GameObject*> Scene::GetObjectsByTag(const std::string& tag) const
{
	std::vector<GameObject*> result;
	for (auto& go : m_vObjects)
	{
		if (!go->IsFlaggedForDeletion() && go->tag == tag) //todo booo, string comparison, boooo!!!
			result.push_back(go.get());
	}
	for (auto& pgo : m_vPendingObjects)
	{
		if (!pgo->IsFlaggedForDeletion() && pgo->tag == tag) //todo booo, string comparison, boooo!!!
			result.push_back(pgo.get());
	}
	return result;
}
void Scene::MarkRenderOrderDirty()
{
	m_DirtyRenderOrder = true;
}
