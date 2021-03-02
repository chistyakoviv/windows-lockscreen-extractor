#pragma once

#include "Window.h"

class Application
{
public:
	Application() = default;
	~Application();

	Window* GetWindow()
	{
		return m_Window;
	}

	void Run();
private:
	Window* m_Window;
};
