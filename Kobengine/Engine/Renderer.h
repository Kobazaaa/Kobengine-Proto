#pragma once
#include <SDL.h>
#include "Singleton.h"
#include "vec3.hpp"

namespace kob
{
	class Texture2D;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ~~	  Simple RAII wrapper for the SDL renderer	
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class Renderer final : public Singleton<Renderer>
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		void Init(SDL_Window* window);
		void Destroy();


		//--------------------------------------------------
		//    Rendering
		//--------------------------------------------------
		void Render() const;

		void RenderTexture(const Texture2D& texture, const glm::vec3& pos, const glm::vec3& size, const glm::vec3& eulerAngles) const;
		void RenderTexture(const Texture2D& texture, const glm::vec3& pos, const glm::vec3& size, const glm::vec3& eulerAngles, const SDL_Rect* srcRect) const;


		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const;
		void SetBackgroundColor(const SDL_Color& color);

	private:
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};
		SDL_Color m_ClearColor{};

		void ImGuiRenderUpdate() const;
		static int GetOpenGLDriverIndex();
	};
}

