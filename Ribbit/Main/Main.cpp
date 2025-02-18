#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Ribbit.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

#include "FPSComponent.h"
#include "ImageRendererComponent.h"
#include "TextRendererComponent.h"

void load()
{
	auto& scene = rib::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<rib::GameObject>();
	go->AddComponent<rib::ImageRendererComponent>("background.tga");
	scene.Add(go);
	
	go = std::make_shared<rib::GameObject>();
	go->AddComponent<rib::ImageRendererComponent>("logo.tga");
	go->SetLocalPosition(glm::vec3(216, 180, 0));
	scene.Add(go);

	auto font = rib::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<rib::GameObject>();
	go->AddComponent<rib::TextRendererComponent>("Programming 4 Assignment", font);
	go->SetLocalPosition(glm::vec3(80, 20, 0));
	scene.Add(go);

	go = std::make_shared<rib::GameObject>();
	go->AddComponent<rib::TextRendererComponent>("FPS", font);
	go->SetLocalPosition(glm::vec3(0, 450, 0));
	go->AddComponent<rib::FPSComponent>();
	scene.Add(go);
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Resources/";
	if(!fs::exists(data_location))
		data_location = "../Resources/";
#endif
	rib::Ribbit engine(data_location);
	engine.Run(load);
    return 0;
}
