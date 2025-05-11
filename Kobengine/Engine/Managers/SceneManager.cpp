#include "SceneManager.h"
#include <algorithm>


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::Scene& kob::SceneManager::CreateScene(const std::string& name)
{

	auto it = std::ranges::find_if(m_vScenes, [name](const std::unique_ptr<Scene>& pScene) { return pScene->GetName() == name; });
	if (it == m_vScenes.end())
	{
		m_vScenes.push_back(std::make_unique<Scene>(name));
		if (m_vScenes.size() == 1)
			m_pActiveScene = m_vScenes[0].get();
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

void kob::SceneManager::SetActiveScene(Scene& scene)
{
	m_pActiveScene->TransferIndependent(&scene);
	m_pActiveScene = &scene;

}
void kob::SceneManager::SetActiveScene(const std::string& name) { if (const auto pScene = GetScene(name)) SetActiveScene(*pScene); }


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::SceneManager::Start()				const { m_pActiveScene->Start(); }
void kob::SceneManager::Update()			const { m_pActiveScene->Update(); }
void kob::SceneManager::LateUpdate()		const { m_pActiveScene->LateUpdate(); }
void kob::SceneManager::FixedUpdate()		const { m_pActiveScene->FixedUpdate(); }
void kob::SceneManager::Render()			const { m_pActiveScene->Render(); }
void kob::SceneManager::ImGuiRenderUpdate() const { m_pActiveScene->ImGuiRenderUpdate(); }
