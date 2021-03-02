#include "Application.h"

#include <iostream>

void Application::Run()
{
	m_Window = new Window(1024, 767);
	std::cout << "Application started" << std::endl;
}

Application::~Application()
{
	delete m_Window;
}
