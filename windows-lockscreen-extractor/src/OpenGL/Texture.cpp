#include "Texture.h"

#include <iostream>

Texture::Texture()
	: m_IsValid(false), m_Width(0), m_Height(0)
{}

Texture::Texture(const std::string& path)
	: m_IsValid(false), m_Width(0), m_Height(0)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = nullptr;
	{
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	}

	if (!data)
	{
		std::cout << "failed to load image" << std::endl;
		return;
	}

	m_Width = width;
	m_Height = height;

	GLenum internalFormat = 0, dataFormat = 0;

	switch (channels)
	{
	case 4:
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
		break;
	case 3:
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
		break;
	}

	if (!(internalFormat & dataFormat))
	{
		std::cout << "format not supported" << std::endl;
		return;
	}

	m_InternalFormat = internalFormat;
	m_DataFormat = dataFormat;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

	glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	m_IsValid = true;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_TextureID);
}

uint32_t Texture::GetTextureID() const
{
	return m_TextureID;
}

uint32_t Texture::GetWidth() const
{
	return m_Width;
}

uint32_t Texture::GetHeight() const
{
	return m_Height;
}

bool Texture::IsValid() const
{
	return m_IsValid;
}
