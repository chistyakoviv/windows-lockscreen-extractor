#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class Panel
{
public:
	Panel() = default;
	~Panel() = default;

	virtual void render() = 0;

	static void Init(GLFWwindow* window);
	static void Begin();
	static void Dockspace();
	static void End();
	static void Shutdown();
};
