#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"

namespace kob
{
	class SceneManager final : public Singleton<SceneManager>
	{
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
	private:
		SceneManager() = default;
	public:
		Scene& CreateScene(const std::string& name);

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		Scene* GetScene(int index) const;
		Scene* GetScene(const std::string& name) const;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Start() const;
		void Update() const;
		void LateUpdate() const;
		void FixedUpdate() const;
		void Render() const;
		void ImGuiRenderUpdate() const;

	private:
		friend class Singleton<SceneManager>;
		std::vector<std::unique_ptr<Scene>> m_vScenes;
	};
}
