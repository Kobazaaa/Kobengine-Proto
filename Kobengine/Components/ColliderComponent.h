#pragma once
#include "Component.h"
#include "glm.hpp"
#include "Renderer.h"
#include "GameObject.h"

namespace kob
{
	class ColliderComponent : public Component
	{
	public:
		

		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit ColliderComponent(GameObject& parent);
		virtual ~ColliderComponent() override;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

		//--------------------------------------------------
		//    Helpers
		//--------------------------------------------------
		void Update() override;
		bool Contains(const glm::vec3& point) const;
		bool Overlaps(const ColliderComponent& coll) const;

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		glm::vec3 GetSize() const;
		void SetSize(const glm::vec3& size);
		glm::vec3 offset{0.f, 0.f, 0.f};

	private:
		glm::vec3 m_Size{10.f, 10.f, 10.f};
	};
}
