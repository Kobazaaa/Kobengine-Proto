#include <SDL.h>
#include <iostream>

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

#include "AchievementManager.h"
#include "IntUIComponent.h"
namespace fs = std::filesystem;

// Managers
#include "InputManager.h"

// Components
#include "FPSComponent.h"
#include "ImageRendererComponent.h"
#include "TextRendererComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

// Commands
#include "MoveCommands.h"
#include "DamageCommand.h"
#include "ScoreCommand.h"

// Events
#include "Event.h"
#include "SteamAchievements.h"

void load()
{
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ~~    Setup
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	using namespace kob;
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto fontL = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto& inputManager = InputManager::GetInstance();
	constexpr float speed = 50.f;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ~~    Background Setup
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	auto go = std::make_shared<GameObject>();
	go->AddComponent<ImageRendererComponent>("background.tga");
	scene.Add(go);
	
	go = std::make_shared<GameObject>();
	go->AddComponent<ImageRendererComponent>("logo.tga");
	go->SetLocalPosition(glm::vec3(216, 180, 0));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<TextRendererComponent>("Programming 4 Assignment", fontL);
	go->SetLocalPosition(glm::vec3(80, 20, 0));
	scene.Add(go);




	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ~~    Character Setup
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Chef
	auto chef = std::make_shared<GameObject>();
	chef->AddComponent<ImageRendererComponent>("Chef.png");
	chef->AddComponent<HealthComponent>(3);
	chef->AddComponent<ScoreComponent>();
	chef->SetLocalPosition(glm::vec3(50, 250, 0));
	scene.Add(chef);

	// Bean
	auto bean = std::make_shared<GameObject>();
	bean->AddComponent<ImageRendererComponent>("Bean.png");
	bean->AddComponent<HealthComponent>(3);
	bean->AddComponent<ScoreComponent>();
	bean->SetLocalPosition(glm::vec3(50, 300, 0));
	scene.Add(bean);


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ~~    UI Setup
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Chef
	auto chefInputUI = std::make_shared<GameObject>();
	chefInputUI->AddComponent<TextRendererComponent>("Use the D-Pad to move the Chef, X to inflict damage, A and B to gain score", fontS);
	chefInputUI->SetLocalPosition(glm::vec3(5, 100, 0));
	scene.Add(chefInputUI);

	// Bean
	auto beanInputUI = std::make_shared<GameObject>();
	beanInputUI->AddComponent<TextRendererComponent>("Use WASD to move the Bean, C to inflict damage, Z and X to gain score", fontS);
	beanInputUI->SetLocalPosition(glm::vec3(5, 120, 0));
	scene.Add(beanInputUI);

	// Fps
	auto fpsUI = std::make_shared<GameObject>();
	fpsUI->AddComponent<TextRendererComponent>("FPS", fontL);
	fpsUI->SetLocalPosition(glm::vec3(0, 450, 0));
	fpsUI->AddComponent<FPSComponent>();
	scene.Add(fpsUI);

	// Health
	auto chefHealth = chef->GetComponent<HealthComponent>();
	auto beanHealth = bean->GetComponent<HealthComponent>();

	auto chefHealthUI = std::make_shared<GameObject>();
	chefHealthUI->AddComponent<TextRendererComponent>("# lives: " + std::to_string(chefHealth->GetMaxLives()), fontS);
	chefHealthUI->AddComponent<IntUIComponent>("# lives: ", chefHealth->GetMaxLives(), "", chefHealth->OnHealthChanged());
	chefHealthUI->SetLocalPosition(glm::vec3(5, 150, 0));
	scene.Add(chefHealthUI);

	auto beanHealthUI = std::make_shared<GameObject>();
	beanHealthUI->AddComponent<TextRendererComponent>("# lives: " + std::to_string(beanHealth->GetMaxLives()), fontS);
	beanHealthUI->AddComponent<IntUIComponent>("# lives: ",beanHealth->GetMaxLives(), "", beanHealth->OnHealthChanged());
	beanHealthUI->SetLocalPosition(glm::vec3(5, 200, 0));
	scene.Add(beanHealthUI);


	// Score
	auto chefScore = chef->GetComponent<ScoreComponent>();
	auto beanScore = bean->GetComponent<ScoreComponent>();

	auto chefScoreUI = std::make_shared<GameObject>();
	chefScoreUI->AddComponent<TextRendererComponent>("Score: 0", fontS);
	chefScoreUI->AddComponent<IntUIComponent>("Score: ", 0, "", chefScore->OnScoreChanged());
	chefScoreUI->SetLocalPosition(glm::vec3(5, 170, 0));
	scene.Add(chefScoreUI);

	auto beanScoreUI = std::make_shared<GameObject>();
	beanScoreUI->AddComponent<TextRendererComponent>("Score: 0", fontS);
	beanScoreUI->AddComponent<IntUIComponent>("Score: ", 0, "", beanScore->OnScoreChanged());
	beanScoreUI->SetLocalPosition(glm::vec3(5, 220, 0));
	scene.Add(beanScoreUI);

	// Achievements
	AchievementManager::GetInstance().RegisterAchievement<int>(beanScore->OnScoreChanged(), std::function([](int score) { return score >= 500; }), "ACH_WIN_ONE_GAME");
	AchievementManager::GetInstance().RegisterAchievement<int>(chefScore->OnScoreChanged(), std::function([](int score) { return score >= 500; }), "ACH_WIN_ONE_GAME");

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ~~    Input Setup
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	inputManager.RegisterGamepad();

	// Chef
	inputManager.RegisterGamepadCmd(Gamepad::Button::DPAD_UP,	 TriggerState::Down, std::make_unique<MoveCommand>(*chef.get(), glm::vec3{ 0, -1, 0 }, 2 * speed), 0);
	inputManager.RegisterGamepadCmd(Gamepad::Button::DPAD_DOWN,  TriggerState::Down, std::make_unique<MoveCommand>(*chef.get(), glm::vec3{ 0,  1, 0 }, 2 * speed), 0);
	inputManager.RegisterGamepadCmd(Gamepad::Button::DPAD_RIGHT, TriggerState::Down, std::make_unique<MoveCommand>(*chef.get(), glm::vec3{ 1,  0, 0 }, 2 * speed), 0);
	inputManager.RegisterGamepadCmd(Gamepad::Button::DPAD_LEFT,  TriggerState::Down, std::make_unique<MoveCommand>(*chef.get(), glm::vec3{ -1,  0, 0 }, 2 * speed), 0);

	inputManager.RegisterGamepadCmd(Gamepad::Button::X, TriggerState::Pressed, std::make_unique<DamageCommand>(*chefHealth), 0);
	inputManager.RegisterGamepadCmd(Gamepad::Button::A, TriggerState::Pressed, std::make_unique<ScoreCommand>(*chefScore, 10), 0);
	inputManager.RegisterGamepadCmd(Gamepad::Button::B, TriggerState::Pressed, std::make_unique<ScoreCommand>(*chefScore, 100), 0);

	// Bean
	inputManager.RegisterKeyboardCmd(SDLK_w, TriggerState::Down, std::make_unique<MoveCommand>(*bean.get(), glm::vec3{ 0, -1, 0 }, speed));
	inputManager.RegisterKeyboardCmd(SDLK_s, TriggerState::Down, std::make_unique<MoveCommand>(*bean.get(), glm::vec3{ 0,  1, 0 }, speed));
	inputManager.RegisterKeyboardCmd(SDLK_d, TriggerState::Down, std::make_unique<MoveCommand>(*bean.get(), glm::vec3{ 1,  0, 0 }, speed));
	inputManager.RegisterKeyboardCmd(SDLK_a, TriggerState::Down, std::make_unique<MoveCommand>(*bean.get(), glm::vec3{-1,  0, 0 }, speed));

	inputManager.RegisterKeyboardCmd(SDLK_c, TriggerState::Pressed, std::make_unique<DamageCommand>(*beanHealth));
	inputManager.RegisterKeyboardCmd(SDLK_z, TriggerState::Pressed, std::make_unique<ScoreCommand>(*beanScore, 10));
	inputManager.RegisterKeyboardCmd(SDLK_x, TriggerState::Pressed, std::make_unique<ScoreCommand>(*beanScore, 100));

}

int main(int, char*[])
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Resources/";
	if(!fs::exists(data_location))
		data_location = "../Resources/";
#endif

	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		kob::AchievementManager::GetInstance().GetSteamAchievementsPtr()->ResetAllAchievements();
		std::cout << "Successfully initialized steam." << std::endl;
	}


	kob::Kobengine engine(data_location);
	engine.Run(load);

	SteamAPI_Shutdown();
    return 0;
}
