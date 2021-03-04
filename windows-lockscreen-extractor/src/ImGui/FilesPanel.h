#pragma once

#include "Panel.h"

class FilesPanel : public Panel
{
public:
	FilesPanel() = default;
	~FilesPanel() = default;

	virtual void render();
};
