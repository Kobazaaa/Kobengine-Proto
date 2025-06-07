#include <stdexcept>
#include <cstring>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
void kob::Renderer::Init(SDL_Window* window)
{
	m_pWindow = window;
	m_pRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_pRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();

	// Enable docking & Viewports
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}
void kob::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();

	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}


//--------------------------------------------------
//    Rendering
//--------------------------------------------------
void kob::Renderer::Render() const
{
	// Clear screen
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_pRenderer);

	// Render
	SceneManager::GetInstance().Render();
	// Render UI
	ImGuiRenderUpdate();

	// Present
	SDL_RenderPresent(m_pRenderer);
}

void kob::Renderer::RenderTexture(const Texture2D& texture, const glm::vec3& pos, const glm::vec3& size, const glm::vec3& eulerAngles) const
{
	SDL_Rect dst{};
	dst.w = abs(static_cast<int>(size.x));
	dst.h = abs(static_cast<int>(size.y));
	dst.x = static_cast<int>(pos.x - dst.w / 2);
	dst.y = static_cast<int>(pos.y - dst.h / 2);
	SDL_Point center = { dst.w / 2, dst.h / 2 };

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, eulerAngles.z, &center, SDL_FLIP_NONE);
}

void kob::Renderer::RenderTexture(const Texture2D& texture, const glm::vec3& pos, const glm::vec3& size, const glm::vec3& eulerAngles, const SDL_Rect* srcRect) const
{
	SDL_Rect dst{};
	dst.w = abs(static_cast<int>(size.x));
	dst.h = abs(static_cast<int>(size.y));
	dst.x = static_cast<int>(pos.x - dst.w / 2);
	dst.y = static_cast<int>(pos.y - dst.h / 2);
	SDL_Point center = { dst.w / 2, dst.h / 2 };

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), srcRect, &dst, eulerAngles.z, &center, SDL_FLIP_NONE);
}

void kob::Renderer::RenderLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color) const
{
	SDL_SetRenderDrawColor(m_pRenderer, static_cast<Uint8>(color.r * 255), static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), static_cast<Uint8>(color.a * 255));
	SDL_RenderDrawLineF(m_pRenderer, p1.x, p1.y, p2.x, p2.y);
}

void kob::Renderer::ImGuiRenderUpdate() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	//ImGui::ShowDemoWindow();
	SceneManager::GetInstance().ImGuiRenderUpdate();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//--------------------------------------------------
//    Accessors & Mutators
//--------------------------------------------------
SDL_Renderer* kob::Renderer::GetSDLRenderer() const
{
	return m_pRenderer;
}

const SDL_Color& kob::Renderer::GetBackgroundColor() const
{
	return m_ClearColor;
}
void kob::Renderer::SetBackgroundColor(const SDL_Color& color)
{
	m_ClearColor = color;
}
void kob::Renderer::SetLogicalSize(int w, int h)
{
	SDL_RenderSetLogicalSize(m_pRenderer, w, h);
}
void kob::Renderer::SetGlobalScale(float s)
{
	SDL_RenderSetScale(m_pRenderer, s, s);
}

int kob::Renderer::GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}
