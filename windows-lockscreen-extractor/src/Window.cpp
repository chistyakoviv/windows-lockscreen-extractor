#include "Window.h"

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
	Shutdown();
}

void Window::OnUpdate()
{
	// Poll and handle events (inputs, window resize, etc.)
	// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
	// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
	// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	glfwPollEvents();

	glfwSwapBuffers(m_Window);
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

	// Handle Window callbacks
	glfwSetWindowUserPointer(m_Window, this);

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		Window& AppWindow = *(Window*)glfwGetWindowUserPointer(window);
		AppWindow.m_Callback(Event(EventType::WindowClose));
	});
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
