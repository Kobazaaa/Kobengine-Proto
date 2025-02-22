#include "ImageRendererComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"


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
	Renderer::GetInstance().RenderTexture(*m_imageTexture, pos.x, pos.y);
}
