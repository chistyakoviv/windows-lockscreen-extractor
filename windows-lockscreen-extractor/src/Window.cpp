#include "Window.h"

#include "ImGui/FilesPanel.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::~Window()
{
	for (auto panel : m_Panels)
	{
		delete panel;
	}
}

void Window::Init()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to init glfw!\n");
		return;
	}

	// Create window with graphics context
	m_Window = glfwCreateWindow(m_Width, m_Height, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
	if (m_Window == NULL)
	{
		fprintf(stderr, "Failed to create GLFWwindow!\n");
		return;
	}

	// Graphics context
	glfwMakeContextCurrent(m_Window);

	//const char* glsl_version = "#version 460";
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only

	bool err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0;

	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return;
	}
	// End graphics context

	glfwSwapInterval(1); // Enable vsync

	Panel::Init(m_Window);

	m_Panels.push_back(new FilesPanel());

	// Main loop
	while (!glfwWindowShouldClose(m_Window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		Panel::Begin();
		Panel::Dockspace();

		// ImGui panels
		for (auto panel : m_Panels)
		{
			panel->render();
		}

		// Demo window for testing features
		// ImGui::ShowDemoWindow();

		Panel::End();

		glfwSwapBuffers(m_Window);
	}

	Panel::Shutdown();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
