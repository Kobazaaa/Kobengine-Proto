#pragma once
#include "Component.h"
#include "vec2.hpp"

namespace rib
{
	class RotateComponent : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit RotateComponent(GameObject& parent, float speed, float radius);


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;

	private:
		glm::vec2 m_CenterPoint	{};
		float m_Speed			{};
		float m_Radius			{};
	};
}
