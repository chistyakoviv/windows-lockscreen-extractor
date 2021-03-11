#include "Application.h"

#include "FileSystem.h"
#include "User.h"
#include "OpenGL/Renderer.h"
#include "OpenGL/Shader.h"

#include <iostream>

#define BIND_FUNCTION(x) [this](auto&&... args) -> decltype(auto) { return this->x(std::forward<decltype(args)>(args)...); }

Application::Application()
{
	m_Window = new Window(1024, 768);
	m_Window->SetCallback(BIND_FUNCTION(Application::OnEvent));

	Panel::Init(m_Window->GetNativeWindow());

	std::vector<std::string> files = FileSystem::ReadDir(User::GetLockScreenImagesDir());

	m_FilesPanel = new FilesPanel();
	m_FilesPanel->SetFiles(files);
	m_FilesPanel->SetCallback(BIND_FUNCTION(Application::OnEvent));

	m_ViewportPanel = new ViewportPanel();

	m_Panels.push_back(m_FilesPanel);
	m_Panels.push_back(m_ViewportPanel);
	
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
	for (auto panel : m_Panels)
	{
		delete panel;
	}
	Panel::Shutdown();
	delete m_Window;
}

void Application::Run()
{
	while (m_Running)
	{
		Panel::Begin();
		Panel::Dockspace();

		// ImGui panels
		for (auto panel : m_Panels)
		{
			panel->render();
		}

		// Demo window for testing features
		 //ImGui::ShowDemoWindow();

		Panel::End();

		m_Window->OnUpdate();
	}
}

void Application::OnEvent(int type)
{
	switch (type)
	{
		case 1:
			Exit();
			break;
		case 2:
			m_ViewportPanel->SetTextureID(m_FilesPanel->GetCurrentTextureID());
			break;
	}
}

void Application::Exit()
{
	m_Running = false;
}
