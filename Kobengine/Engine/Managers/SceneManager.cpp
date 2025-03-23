#include "SceneManager.h"
#include "Scene.h"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::Scene& kob::SceneManager::CreateScene(const std::string& name)
{
	m_vScenes.push_back(std::make_unique<Scene>(name));
	return *m_vScenes.back();
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
