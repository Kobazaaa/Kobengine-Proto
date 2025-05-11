#pragma once
#include "GameObject.h"

namespace kob
{
	class Scene final
	{
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
	public:
		explicit Scene(const std::string& name);
		~Scene() = default;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;


		//--------------------------------------------------
		//    Adding & Removing GameObjects
		//--------------------------------------------------
		GameObject& MoveGameObject(std::unique_ptr<GameObject> object);
		[[nodiscard]] GameObject& AddEmpty(const std::string& name = "GameObject");
		void Remove(const std::unique_ptr<GameObject>& object);
		void RemoveAll();
		void TransferIndependent(Scene* dst);

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Start() const;
		void Update() const;
		void LateUpdate();
		void FixedUpdate() const;
		void Render() const;
		void ImGuiRenderUpdate() const;

		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		const std::string& GetName() const;
		std::vector<GameObject*> GetObjectsByName(const std::string& name) const;

	private:
		void CleanupDeletedObjects();

		inline static unsigned int m_IdCounter = 0;

		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_vObjects{};
	};

}
