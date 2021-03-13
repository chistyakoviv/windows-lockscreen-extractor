#include "Application.h"

#include "OpenGL/Renderer.h"
#include "OpenGL/Shader.h"

#include <iostream>

Application::Application()
{
	m_Window = new Window(1024, 768);
	m_UI = new UI(*this);
	
	Renderer::Init();

	std::string vertex = R"(
		#version 450 core

		void main()
		{
			
		}
	)";

	std::string fragment = R"(
		#version 450 core

		out vec4 color;

		void main()
		{
			color = vec4(0.3, 0.5, 0.4, 1.0);
		}
	)";

	Shader shader(vertex, fragment);
}

Application::~Application()
{
	delete m_UI;
	delete m_Window;
}

void Application::Run()
{
	while (m_Running)
	{
		m_UI->OnUpdate();
		m_Window->OnUpdate();
	}
}

void Application::Exit()
{
	m_Running = false;
}
