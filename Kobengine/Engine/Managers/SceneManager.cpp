#include "SceneManager.h"
#include "Scene.h"

void kob::SceneManager::Start()
{
	for(auto& scene : m_scenes)
	{
		scene->Start();
	}
}

void kob::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void kob::SceneManager::LateUpdate()
{
	for(auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

void kob::SceneManager::FixedUpdate()
{
	for(auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}

void kob::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void kob::SceneManager::ImGuiRenderUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->ImGuiRenderUpdate();
	}
}

kob::Scene& kob::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
