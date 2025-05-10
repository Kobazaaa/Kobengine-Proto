#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "SpriteSheet.h"
#include "vec4.hpp"

namespace kob
{
	class Texture2D;

	class ImageRendererComponent : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructors and Destructors
		//--------------------------------------------------
		explicit ImageRendererComponent(GameObject& parent, const std::string& fileName, const glm::ivec4& srcRect = {-1, -1, -1, -1});
		explicit ImageRendererComponent(GameObject& parent, Texture2D* tex, const glm::ivec4& srcRect = { -1, -1, -1, -1 });
		~ImageRendererComponent() override = default;

		ImageRendererComponent(const ImageRendererComponent& other) = delete;
		ImageRendererComponent(ImageRendererComponent&& other) = delete;
		ImageRendererComponent& operator=(const ImageRendererComponent& other) = delete;
		ImageRendererComponent& operator=(ImageRendererComponent&& other) = delete;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;
		void Render() const override;

		//--------------------------------------------------
		//    Setter
		//--------------------------------------------------
		void SetSourceRect(const glm::ivec4& rect);

	private:
		Texture2D* m_pImageTexture;
		glm::ivec4 m_SrcRect;
	};
}
