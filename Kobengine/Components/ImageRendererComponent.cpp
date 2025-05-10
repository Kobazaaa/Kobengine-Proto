#include "ImageRendererComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"


//--------------------------------------------------
//    Constructors and Destructors
//--------------------------------------------------
kob::ImageRendererComponent::ImageRendererComponent(GameObject& parent, const std::string& fileName, const glm::ivec4& srcRect)
	: Component(parent)
	, m_pImageTexture{ ResourceManager::GetInstance().LoadTexture(fileName) }
{
	if (srcRect == glm::ivec4{ -1,-1,-1,-1 })
		m_SrcRect = { 0, 0, m_pImageTexture->GetSize().x, m_pImageTexture->GetSize().y };
	else
		m_SrcRect = srcRect;
}
kob::ImageRendererComponent::ImageRendererComponent(GameObject& parent, Texture2D* tex, const glm::ivec4& srcRect)
	: Component(parent)
	, m_pImageTexture{ tex }
{
	if (srcRect == glm::ivec4{ -1,-1,-1,-1 })
		m_SrcRect = { 0, 0, m_pImageTexture->GetSize().x, m_pImageTexture->GetSize().y };
	else
		m_SrcRect = srcRect;
}

//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::ImageRendererComponent::Update() {}
void kob::ImageRendererComponent::Render() const
{
	const auto& pos = GetParent()->GetWorldTransform().GetPosition();

	const auto& scale = GetParent()->GetWorldTransform().GetScale();
	const auto& size = glm::vec2(m_SrcRect.z, m_SrcRect.w);
	const auto& dstSize = glm::vec3(static_cast<float>(size.x) * scale.x, static_cast<float>(size.y) * scale.y, 0);

	const auto& eulerAngles = GetParent()->GetWorldTransform().GetEulerRotation();

	SDL_Rect srcRect = { m_SrcRect.x, m_SrcRect.y, m_SrcRect.z, m_SrcRect.w };
	Renderer::GetInstance().RenderTexture(*m_pImageTexture, pos, dstSize, eulerAngles, &srcRect);
}


//--------------------------------------------------
//    Setters
//--------------------------------------------------
void kob::ImageRendererComponent::SetSourceRect(const glm::ivec4& rect) { m_SrcRect = rect; }
