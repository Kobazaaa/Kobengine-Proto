#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Component.h"
#include "Transform.h"

namespace rib
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
		//    Transform
		//--------------------------------------------------
		Transform GetTransform() const;
		void SetPosition(float x, float y);

		//--------------------------------------------------
		//    Deletion
		//--------------------------------------------------
		bool IsFlaggedForDeletion() const;
		void FlagForDeletion();

	private:
		void CleanupDeletedComponents();

		std::vector<std::unique_ptr<Component>> m_vComponents;
		Transform m_transform{};

		bool m_DeletionFlag{ false };
	};
}
