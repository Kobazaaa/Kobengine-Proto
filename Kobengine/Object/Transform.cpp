#include "Transform.h"


//--------------------------------------------------
//    Accessors
//--------------------------------------------------
const glm::vec3& kob::Transform::GetPosition() const
{
	return m_Position;
}
const glm::vec3& kob::Transform::GetEulerRotation() const
{
	return m_EulerAngles;
}
const glm::vec3& kob::Transform::GetScale() const
{
	return m_Scale;
}


//--------------------------------------------------
//    Mutators
//--------------------------------------------------
void kob::Transform::SetPosition(const float x, const float y, const float z)
{
	SetPosition(glm::vec3(x, y, z));
}
void kob::Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

void kob::Transform::SetEulerAngles(float x, float y, float z)
{
	SetEulerAngles(glm::vec3(x, y, z));
}
void kob::Transform::SetEulerAngles(const glm::vec3& angles)
{
	m_EulerAngles = angles;
}

void kob::Transform::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3(x, y, z));
}
void kob::Transform::SetScale(const glm::vec3& scales)
{
	m_Scale = scales;
}
