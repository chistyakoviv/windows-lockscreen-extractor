#include "Application.h"

#include "OpenGL/Renderer.h"

#include <iostream>

Application::Application()
{
	m_Window = new Window(1024, 768);
	m_UI = new UI(*this);
	
	Renderer::Init();
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
