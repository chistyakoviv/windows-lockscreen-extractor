#pragma once

#include "Panel.h"

class ViewportPanel : public Panel
{
public:
	ViewportPanel() = default;
	~ViewportPanel() = default;

	virtual void render() override;
private:

	struct VieportSize
	{
		float x = 0.0f;
		float y = 0.0f;
	};

	VieportSize m_ViewportSize;
};
