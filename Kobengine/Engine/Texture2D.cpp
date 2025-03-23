#include <SDL.h>
#include <SDL_image.h>
#include "Texture2D.h"
#include "Renderer.h"
#include <stdexcept>


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kob::Texture2D::Texture2D(SDL_Texture* texture)
	: m_pTexture{ texture }
{
	assert(m_pTexture != nullptr);
}
kob::Texture2D::Texture2D(const std::string& fullPath)
{
	m_pTexture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (m_pTexture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
}

kob::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}


//--------------------------------------------------
//    Accessors
//--------------------------------------------------
SDL_Texture* kob::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}
glm::ivec2 kob::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}
