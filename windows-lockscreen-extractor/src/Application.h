#pragma once

#include "Window.h"

#include "ImGui/Panel.h"
#include "ImGui/FilesPanel.h"
#include "ImGui/ViewportPanel.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

	Window* GetWindow() const { return m_Window; }
	bool IsRunning() const { return m_Running; }

	void OnEvent();
	void Exit();
private:
	std::vector<Panel*> m_Panels;
	FilesPanel* m_FilesPanel;
	ViewportPanel* m_ViewportPanel;
	Window* m_Window;
	bool m_Running = true;
};
