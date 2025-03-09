#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Kobengine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

#include "FPSComponent.h"
#include "ImageRendererComponent.h"
#include "TextRendererComponent.h"
#include "InputManager.h"
#include "MoveCommands.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>


void load()
{
	using namespace kob;
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent<ImageRendererComponent>("background.tga");
	scene.Add(go);
	
	go = std::make_shared<GameObject>();
	go->AddComponent<ImageRendererComponent>("logo.tga");
	go->SetLocalPosition(glm::vec3(216, 180, 0));
	scene.Add(go);

	auto fontL = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go = std::make_shared<GameObject>();
	go->AddComponent<TextRendererComponent>("Use the D-Pad to move the Chef", fontS);
	go->SetLocalPosition(glm::vec3(5, 100, 0));
	scene.Add(go);
	go = std::make_shared<GameObject>();
	go->AddComponent<TextRendererComponent>("Use WASD to move the HotDog", fontS);
	go->SetLocalPosition(glm::vec3(5, 120, 0));
	scene.Add(go);
	go = std::make_shared<GameObject>();
	go->AddComponent<TextRendererComponent>("Programming 4 Assignment", fontL);
	go->SetLocalPosition(glm::vec3(80, 20, 0));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<TextRendererComponent>("FPS", fontL);
	go->SetLocalPosition(glm::vec3(0, 450, 0));
	go->AddComponent<FPSComponent>();
	scene.Add(go);

	constexpr float speed = 50.f;
	auto& inputManager = InputManager::GetInstance();

	go = std::make_shared<GameObject>();
	go->AddComponent<ImageRendererComponent>("Chef.png");
	go->SetLocalPosition(glm::vec3(50, 250, 0));
	scene.Add(go);
	inputManager.RegisterGamepadCmd<MoveCommand>(XINPUT_GAMEPAD_DPAD_UP,    TriggerState::Down, *go.get(), glm::vec3{ 0, -1, 0 }, 2 * speed);
	inputManager.RegisterGamepadCmd<MoveCommand>(XINPUT_GAMEPAD_DPAD_DOWN,  TriggerState::Down, *go.get(), glm::vec3{ 0,  1, 0 }, 2 * speed);
	inputManager.RegisterGamepadCmd<MoveCommand>(XINPUT_GAMEPAD_DPAD_RIGHT, TriggerState::Down, *go.get(), glm::vec3{ 1,  0, 0 }, 2 * speed);
	inputManager.RegisterGamepadCmd<MoveCommand>(XINPUT_GAMEPAD_DPAD_LEFT,  TriggerState::Down, *go.get(), glm::vec3{-1,  0, 0 }, 2 * speed);

	go = std::make_shared<GameObject>();
	go->AddComponent<ImageRendererComponent>("Bean.png");
	go->SetLocalPosition(glm::vec3(50, 300, 0));
	scene.Add(go);
	inputManager.RegisterKeyboardCmd<MoveCommand>(SDLK_w, TriggerState::Down, *go.get(), glm::vec3{ 0, -1, 0 }, speed);
	inputManager.RegisterKeyboardCmd<MoveCommand>(SDLK_s, TriggerState::Down, *go.get(), glm::vec3{ 0,  1, 0 }, speed);
	inputManager.RegisterKeyboardCmd<MoveCommand>(SDLK_d, TriggerState::Down, *go.get(), glm::vec3{ 1,  0, 0 }, speed);
	inputManager.RegisterKeyboardCmd<MoveCommand>(SDLK_a, TriggerState::Down, *go.get(), glm::vec3{-1,  0, 0 }, speed);
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Resources/";
	if(!fs::exists(data_location))
		data_location = "../Resources/";
#endif
	kob::Kobengine engine(data_location);
	engine.Run(load);
    return 0;
}
