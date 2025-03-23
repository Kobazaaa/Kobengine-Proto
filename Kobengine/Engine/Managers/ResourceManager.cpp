#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

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
std::shared_ptr<kob::Texture2D> kob::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_DataPath/file;
	const auto filename = fs::path(fullPath).filename().string();

	const auto& result = m_mLoadedTextures.insert(std::pair(filename, std::make_shared<Texture2D>(fullPath.string())));
	return result.first->second;
}
std::shared_ptr<kob::Font> kob::ResourceManager::LoadFont(const std::string& file, uint8_t size)
{
	const auto fullPath = m_DataPath/file;
	const auto filename = fs::path(fullPath).filename().string();
	const auto key = std::pair<std::string, uint8_t>(filename, size);

	const auto& result = m_mLoadedFonts.insert(std::pair(key, std::make_shared<Font>(fullPath.string(), size)));
	return result.first->second;
}


void kob::ResourceManager::UnloadUnusedResources()
{
	for (auto it = m_mLoadedTextures.begin(); it != m_mLoadedTextures.end();)
	{
		if (it->second.use_count() == 1)
			it = m_mLoadedTextures.erase(it);
		else
			++it;
	}

	for (auto it = m_mLoadedFonts.begin(); it != m_mLoadedFonts.end();)
	{
		if (it->second.use_count() == 1)
			it = m_mLoadedFonts.erase(it);
		else
			++it;
	}
}