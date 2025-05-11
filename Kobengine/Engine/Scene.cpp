#include "Scene.h"
#include <algorithm>

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
	m_vObjects.emplace_back(std::move(object));
	m_vObjects.back()->OnSceneTransfer(*this);
	return *m_vObjects.back();
}
GameObject& Scene::AddEmpty(const std::string& name)
{
	m_vObjects.emplace_back(std::make_unique<GameObject>(*this, name));
	return *m_vObjects.back();
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
		object->Update();
	}
}
void Scene::LateUpdate()
{
	for(auto& object : m_vObjects)
	{
		object->LateUpdate();
	}
	CleanupDeletedObjects();
}
void Scene::FixedUpdate() const
{
	for(auto& object : m_vObjects)
	{
		object->FixedUpdate();
	}
}
void Scene::Render() const
{
	for (const auto& object : m_vObjects)
	{
		object->Render();
	}
}
void Scene::ImGuiRenderUpdate() const
{
	for (const auto& object : m_vObjects)
	{
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
