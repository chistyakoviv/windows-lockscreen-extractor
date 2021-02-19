#pragma once

#include <cstdint>

class Window
{
public:
	Window(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		Init();
	}
private:
	void Init();
private:
	uint32_t m_Width;
	uint32_t m_Height;
};
