#pragma once

#include "Panel.h"

#include <vector>
#include <string>

class FilesPanel : public Panel
{
public:
	FilesPanel() = default;
	~FilesPanel() = default;

	void setFiles(const std::vector<std::string>& items) { m_Files = items; }

	virtual void render();
private:
	std::vector<std::string> m_Files;
	int32_t m_SelectedFile = -1;
};
