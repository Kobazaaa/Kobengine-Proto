#include "ImageRendererComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"


//--------------------------------------------------
//    Constructors and Destructors
//--------------------------------------------------
rib::ImageRendererComponent::ImageRendererComponent(GameObject& parent, const std::string& fileName)
	: Component(parent)
	, m_imageTexture{ ResourceManager::GetInstance().LoadTexture(fileName) }
{
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void rib::ImageRendererComponent::Update() {}
void rib::ImageRendererComponent::Render() const
{
	const auto& pos = GetParent()->GetWorldTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_imageTexture, pos.x, pos.y);
}
