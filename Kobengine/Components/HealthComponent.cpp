#include "HealthComponent.h"
#include <algorithm>


//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::HealthComponent::HealthComponent(GameObject& parent, int maxLives)
	: Component(parent)
	, m_MaxLives(maxLives)
	, m_CurrentLives(maxLives)
{
}

//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::HealthComponent::Update() {}

//--------------------------------------------------
//    Health
//--------------------------------------------------
void kob::HealthComponent::Damage(int amount)
{
	m_CurrentLives -= amount;
	m_CurrentLives = std::clamp(m_CurrentLives, 0, m_MaxLives);
	if (m_CurrentLives <= 0)
	{
		// OnDeath
	}
}
void kob::HealthComponent::Kill()
{
	m_CurrentLives = 0;
	// OnDeath
}

void kob::HealthComponent::Heal(int amount)
{
	m_CurrentLives += amount;
	m_CurrentLives = std::clamp(m_CurrentLives, 0, m_MaxLives);
}
void kob::HealthComponent::Revive()
{
	m_CurrentLives = m_MaxLives;
}
