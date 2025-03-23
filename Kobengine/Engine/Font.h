#pragma once
#include <string>

struct _TTF_Font;
namespace kob
{
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ~~	  Simple RAII wrapper for a _TTF_Font
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class Font final
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator= (const Font&) = delete;
		Font& operator= (const Font&&) = delete;

		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		_TTF_Font* GetFont() const;

	private:
		_TTF_Font* m_pFont;
	};
}
