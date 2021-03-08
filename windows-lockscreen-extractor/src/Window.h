#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <stddef.h>
#include <stdint.h>
#include <vector>

class Window
{
public:
	using CallbackType = std::function<void()>;

	Window(uint16_t width, uint16_t height)
		: m_Width(width), m_Height(height)
	{
		Init();
	}
	~Window();

	void OnUpdate();

	GLFWwindow* GetNativeWindow() const { return m_Window; }

	void SetCallback(const CallbackType& callback) { Callback = callback; }
private:
	void Init();
	void Shutdown();
private:
	uint16_t m_Width;
	uint16_t m_Height;
	GLFWwindow* m_Window;
	CallbackType Callback;
};
