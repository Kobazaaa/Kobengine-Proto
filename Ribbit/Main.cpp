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
#include "TextRendererComponent.h"
#include "Scene.h"

#include <filesystem>

#include "ImageRendererComponent.h"
namespace fs = std::filesystem;

void load()
{
	auto& scene = rib::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<rib::GameObject>();
	go->AddComponent<rib::ImageRendererComponent>("background.tga");
	scene.Add(go);
	
	go = std::make_shared<rib::GameObject>();
	go->AddComponent<rib::ImageRendererComponent>("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = rib::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<rib::GameObject>();
	go->AddComponent<rib::TextRendererComponent>("Programming 4 Assignment", font);
	go->SetPosition(80, 20);
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
