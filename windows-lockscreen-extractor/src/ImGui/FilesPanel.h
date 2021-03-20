#pragma once

#include "Panel.h"

#include "OpenGL/Texture.h"

#include <vector>
#include <string>
#include <functional>

struct Image
{
	std::wstring origName;
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
	void SetFiles(const std::vector<std::wstring>& items);

	virtual void render() override;

	static uint32_t NO_CURRENT_TEXTURE;
	static int32_t NO_CURRENT_TEXTURE_ID;
private:
	std::vector<Image> FilterImages(const std::vector<std::wstring>& items);
private:
	std::vector<Image> m_Images;
	int32_t m_SelectedImage;
};
