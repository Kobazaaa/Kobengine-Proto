#pragma once
#include "Singleton.h"

namespace kob
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
