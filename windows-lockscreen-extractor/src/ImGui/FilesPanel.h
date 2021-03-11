#pragma once

#include "Panel.h"

#include "OpenGL/Texture.h"

#include <vector>
#include <string>
#include <functional>

struct Image
{
	std::string origName;
	std::string name;
	Texture* texture = nullptr;
};

class FilesPanel : public Panel
{
public:
	using CallbackType = std::function<void(int type)>;

	FilesPanel() = default;
	~FilesPanel() = default;

	uint32_t GetCurrentTextureID() const;
	void SetFiles(const std::vector<std::string>& items);
	void SetCallback(const CallbackType& callback) { Callback = callback; }

	virtual void render() override;
private:

	std::vector<Image> FilterImages(const std::vector<std::string>& items);
private:
	std::vector<Image> m_Images;
	CallbackType Callback;
	int32_t m_SelectedImage = -1;
};
