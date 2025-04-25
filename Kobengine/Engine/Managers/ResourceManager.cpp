#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "ServiceLocator.h"

namespace fs = std::filesystem;


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
void kob::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_DataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}


//--------------------------------------------------
//    Accessors & Mutators
//--------------------------------------------------
kob::Texture2D* kob::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_DataPath/file;
	const auto filename = fs::path(fullPath).filename().string();

	const auto& result = m_mLoadedTextures.insert(std::pair(filename, std::make_unique<Texture2D>(fullPath.string())));
	return result.first->second.get();
}

kob::SpriteSheet* kob::ResourceManager::LoadSpriteSheet(const std::string& file, const std::unordered_map<std::string, SpriteSheetAnimation>& anims)
{
	const auto fullPath = m_DataPath / file;
	const auto filename = fs::path(fullPath).filename().string();

	const auto& result = m_mLoadedSpriteSheets.insert(std::pair(filename, std::make_unique<SpriteSheet>(LoadTexture(file), anims)));
	return result.first->second.get();
}

kob::Font* kob::ResourceManager::LoadFont(const std::string& file, uint8_t size)
{
	const auto fullPath = m_DataPath/file;
	const auto filename = fs::path(fullPath).filename().string();
	const auto key = std::pair(filename, size);

	const auto& result = m_mLoadedFonts.insert(std::pair(key, std::make_unique<Font>(fullPath.string(), size)));
	return result.first->second.get();
}

