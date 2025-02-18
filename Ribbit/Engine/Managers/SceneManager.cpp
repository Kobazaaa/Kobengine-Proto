#include "SceneManager.h"
#include "Scene.h"

void rib::SceneManager::Start()
{
	for(auto& scene : m_scenes)
	{
		scene->Start();
	}
}

void rib::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void rib::SceneManager::LateUpdate()
{
	for(auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

void rib::SceneManager::FixedUpdate()
{
	for(auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}

void rib::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

rib::Scene& rib::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
