#include "ImageRendererComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"


//--------------------------------------------------
//    Constructors and Destructors
//--------------------------------------------------
kob::ImageRendererComponent::ImageRendererComponent(GameObject& parent, const std::string& fileName)
	: Component(parent)
	, m_imageTexture{ ResourceManager::GetInstance().LoadTexture(fileName) }
{
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::ImageRendererComponent::Update() {}
void kob::ImageRendererComponent::Render() const
{
	const auto& pos = GetParent()->GetWorldTransform().GetPosition();

	const auto& scale = GetParent()->GetWorldTransform().GetScale();
	const auto& size = m_imageTexture->GetSize();
	const auto& dstSize = glm::vec3(static_cast<float>(size.x) * scale.x, static_cast<float>(size.y) * scale.y, 0);

	const auto& eulerAngles = GetParent()->GetWorldTransform().GetEulerRotation();

	Renderer::GetInstance().RenderTexture(*m_imageTexture, pos, dstSize, eulerAngles);
}
