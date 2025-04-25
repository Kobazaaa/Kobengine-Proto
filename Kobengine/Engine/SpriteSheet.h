#pragma once
#include <glm.hpp>
#include <vector>
#include <unordered_map>
#include <string>

namespace kob
{
	class Texture2D;
	struct SpriteSheetAnimation
	{
		SpriteSheetAnimation(const std::vector<glm::ivec4>& rects, float secondsPerFrame);
		std::vector<glm::ivec4> animRects;
		float frameDelay;
	};

	struct SpriteSheet final
	{
		SpriteSheet(Texture2D* texturePtr, const std::unordered_map<std::string, SpriteSheetAnimation>& anims = {});
		Texture2D* GetTexture() const;
		SpriteSheetAnimation& GetAnimation(const std::string& animName);
		Texture2D* pTexture;
		std::unordered_map<std::string, SpriteSheetAnimation> animations;
	};
}