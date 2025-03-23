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
GameObject& Scene::Add(std::unique_ptr<GameObject> object)
{
	m_vObjects.emplace_back(std::move(object));
	return *m_vObjects.back();
}
GameObject& Scene::AddEmpty()
{
	m_vObjects.emplace_back(std::make_unique<GameObject>());
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
