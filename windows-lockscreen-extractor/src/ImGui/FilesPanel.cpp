#include "FilesPanel.h"

#include "User.h"

#include <stb_image.h>
#include <iostream>


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

	for (size_t i = 0; i < items.size(); i++)
	{
		const std::string& item = items[i];

		stbi_uc* data = nullptr;
		{
			data = stbi_load(User::GetLockScreenImageAbsolutePath(item).c_str(), &width, &height, &channels, 0);
		}

		if (!data) continue;

		Image image;
		image.origName = item;
		image.name = "Picture " + std::to_string(i);
		image.texture = new Texture(data, width, height, channels);

		images.push_back(image);
		stbi_image_free(data);
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
				Callback(Event(EventType::ChooseFile));
		}
	}

	ImGui::End();
}
