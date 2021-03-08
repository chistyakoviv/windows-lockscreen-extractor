#include "Application.h"

#include "FileSystem.h"
#include "User.h"

#include <iostream>

Application::Application()
{
	m_Window = new Window(1024, 768);

	m_Window->SetCallback([this](auto&&... args) -> decltype(auto) { return this->OnEvent(std::forward<decltype(args)>(args)...); });

	Panel::Init(m_Window->GetNativeWindow());

	std::vector<std::string> files = FileSystem::ReadDir(User::GetLockScreenImagesDir());

	m_FilesPanel = new FilesPanel();
	m_FilesPanel->setFiles(files);

	m_ViewportPanel = new ViewportPanel();

	m_Panels.push_back(m_FilesPanel);
	m_Panels.push_back(m_ViewportPanel);
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

void Application::OnEvent()
{
	Exit();
}

void Application::Exit()
{
	m_Running = false;
}
