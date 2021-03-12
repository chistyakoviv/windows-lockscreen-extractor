#pragma once

#include "Panel.h"

#include "OpenGL/Texture.h"

#include <vector>
#include <string>
#include <functional>

static const uint32_t TEXTURE_MIN_WIDTH = 1920;
static const uint32_t TEXTURE_MIN_HEIGHT = 1080;

struct Image
{
	std::string origName;
	std::string name;
	Texture* texture = nullptr;
};

static bool IsBigTexture(Texture* texture)
{
	return texture->GetWidth() >= TEXTURE_MIN_WIDTH && texture->GetHeight() >= TEXTURE_MIN_HEIGHT;
}

class FilesPanel : public Panel
{
public:
	FilesPanel() = default;
	~FilesPanel();

	uint32_t GetCurrentTextureID() const;
	const Image* GetCurrentImage() const;
	void SetFiles(const std::vector<std::string>& items);

	virtual void render() override;
private:
	std::vector<Image> FilterImages(const std::vector<std::string>& items);
private:
	std::vector<Image> m_Images;
	int32_t m_SelectedImage = -1;
};
