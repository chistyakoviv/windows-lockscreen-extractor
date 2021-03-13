#pragma once

#include "Window.h"
#include "UI.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

	Window* GetWindow() const { return m_Window; }
	bool IsRunning() const { return m_Running; }

	void Exit();
private:
	UI* m_UI;
	Window* m_Window;
	bool m_Running = true;
};
