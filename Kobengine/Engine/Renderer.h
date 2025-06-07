#pragma once
#include <SDL.h>
#include "Singleton.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

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
		void RenderLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color = {1.f, 1.f, 1.f, 1.f}) const;


		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const;
		void SetBackgroundColor(const SDL_Color& color);
		void SetLogicalSize(int w, int h);
		void SetGlobalScale(float s);

	private:
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};
		SDL_Color m_ClearColor{};

		void ImGuiRenderUpdate() const;
		static int GetOpenGLDriverIndex();
	};
}

