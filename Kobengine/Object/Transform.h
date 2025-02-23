#pragma once
#include <glm.hpp>

namespace kob
{
	class Transform final
	{
	public:
		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		const glm::vec3& GetPosition()			const;
		const glm::vec3& GetEulerRotation()		const;
		const glm::vec3& GetScale()				const;

		//--------------------------------------------------
		//    Mutators
		//--------------------------------------------------
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);
		void SetEulerAngles(float x, float y, float z);
		void SetEulerAngles(const glm::vec3& angles);
		void SetScale(float x, float y, float z);
		void SetScale(const glm::vec3& scales);

	private:
		glm::vec3 m_Position	{ 0.f, 0.f, 0.f };
		glm::vec3 m_EulerAngles	{ 0.f, 0.f, 0.f };
		glm::vec3 m_Scale		{ 1.f, 1.f, 1.f };
	};
}
