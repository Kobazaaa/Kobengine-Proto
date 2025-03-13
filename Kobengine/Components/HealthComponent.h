#pragma once
#include "Component.h"

namespace kob
{
	class HealthComponent final : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructor
		//--------------------------------------------------
		explicit HealthComponent(GameObject& parent, int maxLives);


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;


		//--------------------------------------------------
		//    Health
		//--------------------------------------------------
		void Damage(int amount = 1);
		void Kill();
		void Heal(int amount = 1);
		void Revive();

	private:
		int m_MaxLives;
		int m_CurrentLives;
	};
}
