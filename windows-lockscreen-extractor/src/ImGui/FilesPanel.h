#pragma once

#include "Panel.h"

#include "OpenGL/Texture.h"

#include <vector>
#include <string>

struct Image
{
	std::string origName;
	std::string name;
	Texture texture;
};

class FilesPanel : public Panel
{
public:
	FilesPanel() = default;
	~FilesPanel() = default;

	void SetFiles(const std::vector<std::string>& items);

	virtual void render() override;
private:

	std::vector<Image> FilterImages(const std::vector<std::string>& items);
private:
	std::vector<Image> m_Images;
	int32_t m_SelectedImage = -1;
};
