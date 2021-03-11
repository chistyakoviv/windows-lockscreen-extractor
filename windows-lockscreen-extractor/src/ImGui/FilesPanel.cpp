#include "FilesPanel.h"

#include "User.h"

#include <iostream>

FilesPanel::~FilesPanel()
{
	for (auto image : m_Images)
	{
		delete image.texture;
	}
}

uint32_t FilesPanel::GetCurrentTextureID() const
{
	if (m_SelectedImage == -1)
		return 0;

	return m_Images[m_SelectedImage].texture->GetTextureID();
}

void FilesPanel::SetFiles(const std::vector<std::string>& items)
{
	m_Images = FilterImages(items);
}

std::vector<Image> FilesPanel::FilterImages(const std::vector<std::string>& items)
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
