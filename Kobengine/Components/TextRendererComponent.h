#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"

namespace kob
{
	class Font;
	class Texture2D;
	class TextRendererComponent final : public Component
	{
	public:

		//--------------------------------------------------
		//    Constructors and Destructors
		//--------------------------------------------------
		explicit TextRendererComponent(GameObject& parent, const std::string& text, Font* font);
		~TextRendererComponent() override = default;

		TextRendererComponent(const TextRendererComponent& other) = delete;
		TextRendererComponent(TextRendererComponent&& other) = delete;
		TextRendererComponent& operator=(const TextRendererComponent& other) = delete;
		TextRendererComponent& operator=(TextRendererComponent&& other) = delete;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void Update() override;
		void Render() const override;


		//--------------------------------------------------
		//    Text
		//--------------------------------------------------
		void SetText(const std::string& text);


	private:
		bool m_needsUpdate;
		std::string m_text;
		Font* m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
