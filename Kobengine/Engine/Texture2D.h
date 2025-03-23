#pragma once
#include <vec2.hpp>
#include <string>

struct SDL_Texture;
namespace kob
{
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ~~	  Simple RAII wrapper for an SDL_Texture	
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class Texture2D final
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Texture2D(SDL_Texture* texture);
		explicit Texture2D(const std::string& fullPath);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		SDL_Texture* GetSDLTexture() const;
		glm::ivec2 GetSize() const;

	private:
		SDL_Texture* m_Texture;
	};
}
