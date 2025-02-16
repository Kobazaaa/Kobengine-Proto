#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace rib;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

void Scene::CleanupDeletedObjects()
{
	m_objects.erase(
		std::remove_if(m_objects.begin(), m_objects.end(),
			[](const std::shared_ptr<GameObject>& object)
			{
				return object->IsFlaggedForDeletion();
			}),
		m_objects.end());
}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
	CleanupDeletedObjects();
}

void Scene::FixedUpdate()
{
	for(auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

