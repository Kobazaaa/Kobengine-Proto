#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace rib
{
	class Texture2D;

	class ImageRendererComponent : public Component
	{
	public:
		//--------------------------------------------------
		//    Constructors and Destructors
		//--------------------------------------------------
		explicit ImageRendererComponent(GameObject* parent, const std::string& fileName);
		~ImageRendererComponent() override = default;

		ImageRendererComponent(const ImageRendererComponent& other) = delete;
		ImageRendererComponent(ImageRendererComponent&& other) = delete;
		ImageRendererComponent& operator=(const ImageRendererComponent& other) = delete;
		ImageRendererComponent& operator=(ImageRendererComponent&& other) = delete;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_imageTexture;
	};
}
