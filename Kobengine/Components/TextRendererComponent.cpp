#include <stdexcept>
#include <SDL_ttf.h>
#include "TextRendererComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"


//--------------------------------------------------
//    Constructors and Destructors
//--------------------------------------------------
kob::TextRendererComponent::TextRendererComponent(GameObject& parent, const std::string& text, std::shared_ptr<Font> font)
	: Component(parent), m_needsUpdate(true), m_text(text), m_font(std::move(font)), m_textTexture(nullptr)
{ }


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::TextRendererComponent::Update()
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}
void kob::TextRendererComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = GetParent()->GetWorldTransform().GetPosition();

		const auto& scale = GetParent()->GetWorldTransform().GetScale();
		const auto& size = m_textTexture->GetSize();
		const auto& dstSize = glm::vec3(static_cast<float>(size.x) * scale.x, static_cast<float>(size.y) * scale.y, 0);

		const auto& eulerAngles = GetParent()->GetWorldTransform().GetEulerRotation();

		Renderer::GetInstance().RenderTexture(*m_textTexture, pos, dstSize, eulerAngles);
	}
}


//--------------------------------------------------
//    Text
//--------------------------------------------------

// This implementation uses the "dirty flag" pattern
void kob::TextRendererComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

