#include "TrashTheCacheComponent.h"

kob::TrashTheCacheComponent::TrashTheCacheComponent(GameObject& parent)
	: Component(parent)
{}

void kob::TrashTheCacheComponent::Start()
{
}

void kob::TrashTheCacheComponent::Update() {}

void kob::TrashTheCacheComponent::ImGuiRenderUpdate()
{
	ImGui::Begin("Trash The Cache");

	ImGui::End();
}
