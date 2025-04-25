#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>
#include <unordered_map>

#include "Singleton.h"
#include "Texture2D.h"
#include "Font.h"
#include "SpriteSheet.h"

namespace kob
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
	private:
		ResourceManager() = default;
	public:
		void Init(const std::filesystem::path& data);

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		Texture2D* LoadTexture(const std::string& file);
		SpriteSheet* LoadSpriteSheet(const std::string& file, const std::unordered_map<std::string, SpriteSheetAnimation>& anims = {});
		Font* LoadFont(const std::string& file, uint8_t size);
	private:
		friend class Singleton<ResourceManager>;

		std::filesystem::path m_DataPath;

		std::map<std::string, std::unique_ptr<Texture2D>> m_mLoadedTextures;
		std::map<std::string, std::unique_ptr<SpriteSheet>> m_mLoadedSpriteSheets;
		std::map<std::pair<std::string, uint8_t>, std::unique_ptr<Font>> m_mLoadedFonts;

	};
}
