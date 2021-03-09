#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(uint32_t slot) const;
	uint32_t GetTextureID() const;
private:
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_TextureID;

	GLenum m_InternalFormat;
	GLenum m_DataFormat;
};
