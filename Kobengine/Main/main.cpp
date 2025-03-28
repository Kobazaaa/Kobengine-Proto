#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Kobengine.h"

int main(int, char*[])
{
	// Create Engine
	kob::Kobengine engine{};

	// Run Engine
	engine.Setup(); // Needs to be defined by the user of the engine for their project
	engine.Run();

    return 0;
}
