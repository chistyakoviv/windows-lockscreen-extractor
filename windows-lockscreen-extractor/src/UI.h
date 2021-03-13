#pragma once

#include "Base.h"
#include "Window.h"
#include "ImGui/Panel.h"
#include "ImGui/FilesPanel.h"
#include "ImGui/ViewportPanel.h"
#include "OpenGL/Texture.h"
#include "Events/Event.h"

class Application;

class UI
{
public:
	UI(Application& app);
	~UI();

	void OnEvent(Event event);
	void OnUpdate();
private:
	std::vector<Panel*> m_Panels;
	FilesPanel* m_FilesPanel;
	ViewportPanel* m_ViewportPanel;
	Application& m_App;
};
