#include "MoveCommands.h"
#include "Timer.h"

kob::MoveCommand::MoveCommand(GameObject& gameobject, const glm::vec3& dir, float speed)
	: m_pGameObject{ &gameobject }
	, m_Direction{ dir }
	, m_Speed{ speed }
{
}

void kob::MoveCommand::Execute()
{
	const auto& currPos = m_pGameObject->GetLocalTransform().GetPosition();
	const auto newPos = currPos + m_Direction * m_Speed * Timer::GetDeltaSeconds();
	m_pGameObject->SetLocalPosition(newPos);
}
