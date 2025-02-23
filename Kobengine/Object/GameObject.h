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
		GameObject() = default;
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
		void AddComponent(Args&&... args)
		{
			m_vComponents.push_back(std::make_unique<ComponentType>(*this, std::forward<Args>(args)...));
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
		const Transform& GetLocalTransform() const;
		const Transform& GetWorldTransform();
		void			 SetLocalPosition(const glm::vec3& pos);
		void			 UpdateWorldPosition();

		//--------------------------------------------------
		//    Flags
		//--------------------------------------------------
		bool IsFlaggedForDeletion() const;
		void FlagForDeletion();
		void SetPositionDirty();

	private:
		void CleanupDeletedComponents();
		std::vector<std::unique_ptr<Component>> m_vComponents;

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		GameObject* m_pParent{};
		std::vector<GameObject*> m_vChildren{};

		Transform m_LocalTransform{};
		Transform m_WorldTransform{};

		bool m_DeletionFlag{ false };
		bool m_DirtyPositionFlag{ false };
	};
}
