#include "SpriteSheet.h"

#include "Texture2D.h"

kob::SpriteSheetAnimation::SpriteSheetAnimation(const std::vector<glm::ivec4>& rects, float secondsPerFrame)
	: animRects(rects)
	, frameDelay(secondsPerFrame)
{}

kob::SpriteSheet::SpriteSheet(Texture2D* texturePtr, const std::unordered_map<std::string, SpriteSheetAnimation>& anims)
	: pTexture(texturePtr)
	, animations(anims)
{}

kob::Texture2D* kob::SpriteSheet::GetTexture() const
{
	return pTexture;
}

kob::SpriteSheetAnimation* kob::SpriteSheet::GetAnimation(const std::string& animName)
{
	if (!animations.contains(animName))
		return nullptr;
	return &animations.at(animName);
}
