#include "Application.h"
#include "Window.h"

#include <iostream>

void Application::Run()
{
	Window window(1024, 767);
	std::cout << "Application started" << std::endl;
}
