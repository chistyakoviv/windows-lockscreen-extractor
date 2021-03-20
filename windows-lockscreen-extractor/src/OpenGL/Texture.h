#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::wstring& path);
	~Texture();

	void Bind(uint32_t slot) const;
	uint32_t GetTextureID() const;
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	bool IsValid() const;
private:
	bool m_IsValid;
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_TextureID;

	GLenum m_InternalFormat;
	GLenum m_DataFormat;
};
