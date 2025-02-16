#pragma once
#include "Singleton.h"

namespace rib
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
