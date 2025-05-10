#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Component.h"
#include "Transform.h"

namespace kob
{
	class Texture2D;

	class GameObject final
	{
	public:
		//--------------------------------------------------
		//    Constructors and Destructors
		//--------------------------------------------------
		explicit GameObject(const std::string& name ="GameObject");
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Start();
		void Update();
		void LateUpdate();
		void FixedUpdate();
		void Render() const;
		void ImGuiRenderUpdate();


		//--------------------------------------------------
		//    Components
		//--------------------------------------------------
		template <typename ComponentType>
			requires std::derived_from<ComponentType, Component>
		[[nodiscard]] bool HasComponent() const
		{
			for (const auto& component : m_vComponents)
			{
				auto castedComponent = dynamic_cast<ComponentType>(component.get());
				if (castedComponent) return true;
			}
			return false;
		}
		template <typename ComponentType>
			requires std::derived_from<ComponentType, Component>
		[[nodiscard]] ComponentType* GetComponent(int index = 0)
		{
			int componentCount = 0;
			for (const auto& component : m_vComponents)
			{
				auto castedComponent = dynamic_cast<ComponentType*>(component.get());
				if (castedComponent)
				{
					if (componentCount == index) return castedComponent;
					++componentCount;
				}
			}
			return nullptr;
		}
		template <typename ComponentType, typename... Args>
			requires std::derived_from<ComponentType, Component>
		ComponentType* AddComponent(Args&&... args)
		{
			m_vComponents.push_back(std::make_unique<ComponentType>(*this, std::forward<Args>(args)...));
			return dynamic_cast<ComponentType*>(m_vComponents.back().get());
		}
		template <typename ComponentType>
			requires std::derived_from<ComponentType, Component>
		void RemoveComponent(int index = 0)
		{
			int componentCount = 0;
			for (const auto& component : m_vComponents)
			{
				auto castedComponent = std::dynamic_pointer_cast<ComponentType>(component);
				if (castedComponent)
				{
					if (componentCount == index) castedComponent->MarkForDeletion();
					++componentCount;
				}
			}
		}

		//--------------------------------------------------
		//    Parent-Child
		//--------------------------------------------------
		GameObject* GetParent()								const;
		void		SetParent(GameObject* parent, bool keepWorldPosition);
		bool		IsChild(const GameObject* child)		const;
		int			GetChildCount()							const;
		GameObject* GetChildAt(int index)					const;
		const std::vector<GameObject*>& GetAllChildren()	const;

		//--------------------------------------------------
		//    Transform
		//--------------------------------------------------
		const Transform&   GetLocalTransform() const;
		const Transform&   GetWorldTransform();
		void			   SetLocalPosition(const glm::vec3& pos);
		void			   SetLocalScale(const glm::vec3& scale);
		void			   SetLocalRotation(const glm::vec3& eulerAngles);
		void			   UpdateWorldPosition();
		void			   SetName(const std::string& name);
		const std::string& GetName() const;

		//--------------------------------------------------
		//    Flags
		//--------------------------------------------------
		bool IsFlaggedForDeletion() const;
		void FlagForDeletion();
		void SetTransformDirty();

	private:
		void CleanupDeletedComponents();
		std::vector<std::unique_ptr<Component>> m_vComponents;

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		GameObject* m_pParent{};
		std::vector<GameObject*> m_vChildren{};

		std::string m_Name{"GameObject"};

		Transform m_LocalTransform{};
		Transform m_WorldTransform{};

		bool m_DeletionFlag{ false };
		bool m_DirtyTransformFlag{ false };
	};
}
