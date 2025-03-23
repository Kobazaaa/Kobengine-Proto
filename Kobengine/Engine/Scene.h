#pragma once
#include "SceneManager.h"

namespace kob
{
	class GameObject;
	class Scene final
	{
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
	private:
		explicit Scene(const std::string& name);
	public:
		~Scene() = default;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;


		//--------------------------------------------------
		//    Adding & Removing GameObjects
		//--------------------------------------------------
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const std::unique_ptr<GameObject>& object);
		void RemoveAll();


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Start() const;
		void Update() const;
		void LateUpdate();
		void FixedUpdate() const;
		void Render() const;
		void ImGuiRenderUpdate() const;

	private:
		friend Scene& SceneManager::CreateScene(const std::string& name);
		void CleanupDeletedObjects();

		inline static unsigned int m_IdCounter = 0;

		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_vObjects{};
	};

}
