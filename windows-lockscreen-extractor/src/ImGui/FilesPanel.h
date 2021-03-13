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

class FilesPanel : public Panel
{
public:
	FilesPanel();
	~FilesPanel();

	uint32_t GetCurrentTextureID() const;
	const Image* GetCurrentImage() const;
	void SetFiles(const std::vector<std::string>& items);

	virtual void render() override;

	static uint32_t NO_CURRENT_TEXTURE;
	static int32_t NO_CURRENT_TEXTURE_ID;
private:
	std::vector<Image> FilterImages(const std::vector<std::string>& items);
private:
	std::vector<Image> m_Images;
	int32_t m_SelectedImage;
};
