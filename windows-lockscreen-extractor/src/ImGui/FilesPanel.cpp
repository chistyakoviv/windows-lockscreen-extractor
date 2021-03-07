#include "FilesPanel.h"

void FilesPanel::render()
{
	ImGui::Begin("Available Files");

	for (size_t i = 0; i < m_Files.size(); i++)
	{
		if (ImGui::Selectable(m_Files[i].c_str(), m_SelectedFile == i))
			m_SelectedFile = i;
	}

	ImGui::End();
}
