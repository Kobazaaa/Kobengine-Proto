#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

rib::GameObject::~GameObject() = default;

void rib::GameObject::Update(){}

void rib::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void rib::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void rib::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
