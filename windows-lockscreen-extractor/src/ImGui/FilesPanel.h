#pragma once

#include "Panel.h"

#include "OpenGL/Texture.h"
#include "Events/Event.h"

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
	using CallbackType = std::function<void(Event event)>;

	FilesPanel() = default;
	~FilesPanel();

	uint32_t GetCurrentTextureID() const;
	void SetFiles(const std::vector<std::string>& items);
	void SetCallback(const CallbackType& callback) { m_Callback = callback; }

	virtual void render() override;
private:
	std::vector<Image> FilterImages(const std::vector<std::string>& items);
private:
	std::vector<Image> m_Images;
	CallbackType m_Callback;
	int32_t m_SelectedImage = -1;
};
