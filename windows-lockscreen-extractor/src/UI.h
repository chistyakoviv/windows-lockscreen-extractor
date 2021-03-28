#pragma once

#include "Window.h"
#include "ImGui/Panel.h"
#include "ImGui/FilesPanel.h"
#include "ImGui/ViewportPanel.h"
#include "OpenGL/Texture.h"
#include "OpenGL/Framebuffer.h"
#include "OpenGL/Shader.h"
#include "Events/Event.h"

#define BIND_FUNCTION(x) [this](auto&&... args) -> decltype(auto) { return this->x(std::forward<decltype(args)>(args)...); }

class Application;

class UI
{
public:
	UI(Application& app);
	~UI();

	void OnEvent(Event event);
	void OnUpdate();
	void OnSave();

	void Init();
	void Begin();
	void Dockspace();
	void End();
	void Shutdown();
private:
	std::vector<Panel*> m_Panels;
	Framebuffer* m_Framebuffer;
	Shader* m_Shader;
	uint32_t m_QuadVAO, m_QuadVBO;
	FilesPanel* m_FilesPanel;
	ViewportPanel* m_ViewportPanel;
	Application& m_App;
};
