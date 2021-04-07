//! @file Font.hpp

#pragma once

#include "../main.hpp"

class sdl_stb_font_cache;

class Font {
private:
	Font() = default;
	Font(const char* _name);
	Font(const Font&) = delete;
	Font(Font&&) = delete;
	~Font();

	Font& operator=(const Font&) = delete;
	Font& operator=(Font&&) = delete;

	struct FontFile
	{
		size_t buffer_size;
		uint8_t* buffer;

		FontFile(size_t buffer_size, uint8_t* buffer)
			: buffer_size(buffer_size),
			buffer(buffer)
		{
		}

		~FontFile()
		{
			delete[] buffer;
		}
	};

	FontFile* loadFontFile(string filepath);

public:
	//! built-in font
	static const char* defaultFont;

	const char*		getName() const { return name.c_str(); }
	//TTF_Font*		getTTF() { return font; }
	sdl_stb_font_cache* getTTF() { return fontcache; }
	int				getOutline() { return outlineSize; }

	//! get the size of the given text string in pixels
	//! @param str the utf-8 string to get the size of
	//! @param out_w the integer to hold the width
	//! @param out_h the integer to hold the height
	//! @return 0 on success, non-zero on error
	int sizeText(const char* str, int* out_w, int* out_h) const;

	//! get the height of the font
	//! @return the font height in pixels
	int height() const;

	//! get a Font object from the engine
	//! @param name The Font name
	//! @return the Font or nullptr if it could not be retrieved
	static Font* get(const char* name);

	//! dump engine's font cache
	static void dumpCache();

private:
	std::string name;
	//TTF_Font* font = nullptr;
	sdl_stb_font_cache* fontcache = nullptr;
	FontFile* fontFile = nullptr;
	int pointSize = 16;
	int outlineSize = 0;
};