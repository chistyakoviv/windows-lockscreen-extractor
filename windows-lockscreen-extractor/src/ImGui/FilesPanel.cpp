#include "FilesPanel.h"

#include "Helpers/User.h"

#include <iostream>

static const uint32_t TEXTURE_MIN_WIDTH = 1920;
static const uint32_t TEXTURE_MIN_HEIGHT = 1080;

static bool IsBigTexture(Texture* texture)
{
	return texture->GetWidth() >= TEXTURE_MIN_WIDTH && texture->GetHeight() >= TEXTURE_MIN_HEIGHT;
}

uint32_t FilesPanel::NO_CURRENT_TEXTURE = -1;
int32_t FilesPanel::NO_CURRENT_TEXTURE_ID = 0;

FilesPanel::FilesPanel()
	: m_SelectedImage(NO_CURRENT_TEXTURE)
{}

FilesPanel::~FilesPanel()
{
	for (auto image : m_Images)
	{
		delete image.texture;
	}
}

uint32_t FilesPanel::GetCurrentTextureID() const
{
	if (m_SelectedImage == NO_CURRENT_TEXTURE)
		return NO_CURRENT_TEXTURE_ID;

	return m_Images[m_SelectedImage].texture->GetTextureID();
}

const Image* FilesPanel::GetCurrentImage() const
{
	if (m_SelectedImage == NO_CURRENT_TEXTURE)
		return nullptr;

	return &m_Images[m_SelectedImage];
}

void FilesPanel::SetFiles(const std::vector<std::wstring>& items)
{
	m_Images = FilterImages(items);
}

std::vector<Image> FilesPanel::FilterImages(const std::vector<std::wstring>& items)
{
	std::vector<Image> images;

	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);

	size_t pictureCounter = 0;
	for (size_t i = 0; i < items.size(); i++)
	{
		Texture* texture = new Texture(User::GetLockScreenImageAbsolutePath(items[i]));

		if (!texture->IsValid() || !IsBigTexture(texture))
		{
			delete texture;
			continue;
		}

		Image image;
		image.origName = items[i];
		image.name = "Picture " + std::to_string(pictureCounter);
		image.texture = texture;

		images.push_back(image);
		pictureCounter++;
	}

	return images;
}

void FilesPanel::render()
{
	ImGui::Begin("Available Files");

	for (size_t i = 0; i < m_Images.size(); i++)
	{
		if (ImGui::Selectable(m_Images[i].name.c_str(), m_SelectedImage == i))
		{
			size_t prev = m_SelectedImage;
			m_SelectedImage = i;

			if (prev != i)
				m_Callback(Event(EventType::ChooseFile));
		}
	}

	ImGui::End();
}
