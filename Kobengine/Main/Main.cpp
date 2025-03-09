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
	auto& scene = kob::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::ImageRendererComponent>("background.tga");
	scene.Add(go);
	
	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::ImageRendererComponent>("logo.tga");
	go->SetLocalPosition(glm::vec3(216, 180, 0));
	scene.Add(go);

	auto font = kob::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::TextRendererComponent>("Programming 4 Assignment", font);
	go->SetLocalPosition(glm::vec3(80, 20, 0));
	scene.Add(go);

	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::TextRendererComponent>("FPS", font);
	go->SetLocalPosition(glm::vec3(0, 450, 0));
	go->AddComponent<kob::FPSComponent>();
	scene.Add(go);

	constexpr float speed = 50.f;
	auto& inputManager = kob::InputManager::GetInstance();
	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::ImageRendererComponent>("Chef.png");
	go->SetLocalPosition(glm::vec3(50, 250, 0));
	scene.Add(go);
	inputManager.RegisterGamepadButton(XINPUT_GAMEPAD_DPAD_UP,	  std::make_unique<kob::MoveCommand>(*go.get(), glm::vec3{ 0, -1, 0 }, speed), kob::TriggerState::Down);
	inputManager.RegisterGamepadButton(XINPUT_GAMEPAD_DPAD_DOWN,  std::make_unique<kob::MoveCommand>(*go.get(), glm::vec3{ 0,  1, 0 }, speed), kob::TriggerState::Down);
	inputManager.RegisterGamepadButton(XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<kob::MoveCommand>(*go.get(), glm::vec3{ 1,  0, 0 }, speed), kob::TriggerState::Down);
	inputManager.RegisterGamepadButton(XINPUT_GAMEPAD_DPAD_LEFT,  std::make_unique<kob::MoveCommand>(*go.get(), glm::vec3{-1,  0, 0 }, speed), kob::TriggerState::Down);

	go = std::make_shared<kob::GameObject>();
	go->AddComponent<kob::ImageRendererComponent>("Bean.png");
	go->SetLocalPosition(glm::vec3(50, 300, 0));
	scene.Add(go);
	inputManager.RegisterKeyboardKey(SDLK_w, std::make_unique<kob::MoveCommand>(*go.get(), glm::vec3{ 0, -1, 0 }, 2 * speed), kob::TriggerState::Down);
	inputManager.RegisterKeyboardKey(SDLK_s, std::make_unique<kob::MoveCommand>(*go.get(), glm::vec3{ 0,  1, 0 }, 2 * speed), kob::TriggerState::Down);
	inputManager.RegisterKeyboardKey(SDLK_d, std::make_unique<kob::MoveCommand>(*go.get(), glm::vec3{ 1,  0, 0 }, 2 * speed), kob::TriggerState::Down);
	inputManager.RegisterKeyboardKey(SDLK_a, std::make_unique<kob::MoveCommand>(*go.get(), glm::vec3{-1,  0, 0 }, 2 * speed), kob::TriggerState::Down);
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
