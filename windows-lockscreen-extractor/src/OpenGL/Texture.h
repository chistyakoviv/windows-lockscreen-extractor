#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string>

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& path);
	Texture(stbi_uc* data, int width, int height, int channels);
	~Texture();

	void Bind(uint32_t slot) const;
	uint32_t GetTextureID() const;
private:
	bool CreateTexture(stbi_uc* data, int width, int height, int channels);
private:
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_TextureID;

	GLenum m_InternalFormat;
	GLenum m_DataFormat;
};
