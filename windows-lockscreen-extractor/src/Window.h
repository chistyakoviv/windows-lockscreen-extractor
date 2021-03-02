#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>

class Window
{
public:
	Window(uint16_t width, uint16_t height)
		: m_Width(width), m_Height(height)
	{
		Init();
	}

	static void ImGuiBegin();
	static void ImGuiEnd(GLFWwindow* window);
	static void ImGuiDock();
private:
	void Init();
private:
	uint16_t m_Width;
	uint16_t m_Height;
	GLFWwindow* m_Window;
};
