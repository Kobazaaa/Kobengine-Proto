#include "SceneManager.h"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::Scene& kob::SceneManager::CreateScene(const std::string& name)
{
	auto it = std::ranges::find_if(m_vScenes, [name](const std::unique_ptr<Scene>& pScene) { return pScene->GetName() == name; });
	if (it == m_vScenes.end())
	{
		m_vScenes.push_back(std::make_unique<Scene>(name));
		return *m_vScenes.back();
	}
	return **it;
}


//--------------------------------------------------
//    Accessors & Mutators
//--------------------------------------------------
kob::Scene* kob::SceneManager::GetScene(int index) const
{
	if (index < 0 || index >= static_cast<int>(m_vScenes.size()))
		return nullptr;
	return m_vScenes[index].get();
}
kob::Scene* kob::SceneManager::GetScene(const std::string& name) const
{
	for (auto& scene : m_vScenes)
		if (scene->GetName() == name)
			return scene.get();
	return nullptr;
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::SceneManager::Start() const
{
	for(auto& scene : m_vScenes)
	{
		scene->Start();
	}
}
void kob::SceneManager::Update() const
{
	for(auto& scene : m_vScenes)
	{
		scene->Update();
	}
}
void kob::SceneManager::LateUpdate() const
{
	for(auto& scene : m_vScenes)
	{
		scene->LateUpdate();
	}
}
void kob::SceneManager::FixedUpdate() const
{
	for(auto& scene : m_vScenes)
	{
		scene->FixedUpdate();
	}
}
void kob::SceneManager::Render() const
{
	for (const auto& scene : m_vScenes)
	{
		scene->Render();
	}
}
void kob::SceneManager::ImGuiRenderUpdate() const
{
	for (const auto& scene : m_vScenes)
	{
		scene->ImGuiRenderUpdate();
	}
}
