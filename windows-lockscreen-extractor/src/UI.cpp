#include "UI.h"

#include "Application.h"
#include "FileSystem.h"
#include "User.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

UI::UI(Application& app)
	: m_App(app)
{
	m_App.GetWindow()->SetCallback(BIND_FUNCTION(UI::OnEvent));

	Panel::Init(m_App.GetWindow()->GetNativeWindow());
	Panel::SetStaticCallback(BIND_FUNCTION(UI::OnEvent));

	std::vector<std::string> files = FileSystem::ReadDir(User::GetLockScreenImagesDir());

	m_FilesPanel = new FilesPanel();
	m_FilesPanel->SetFiles(files);
	m_FilesPanel->SetCallback(BIND_FUNCTION(UI::OnEvent));

	m_ViewportPanel = new ViewportPanel();

	m_Panels.push_back(m_FilesPanel);
	m_Panels.push_back(m_ViewportPanel);
}

UI::~UI()
{
	for (auto panel : m_Panels)
	{
		delete panel;
	}
	Panel::Shutdown();
}

void UI::OnEvent(Event event)
{

	switch (event.GetType())
	{
	case EventType::WindowClose:
		m_App.Exit();
		break;
	case EventType::ChooseFile:
		m_ViewportPanel->SetTextureID(m_FilesPanel->GetCurrentTextureID());
		break;
	case EventType::SaveFile:
		std::string* filepath = (std::string*)event.GetData();
		const Image* img = m_FilesPanel->GetCurrentImage();

		int width, height, channels;
		stbi_uc* data = nullptr;
		{
			data = stbi_load(User::GetLockScreenImageAbsolutePath(img->origName).c_str(), &width, &height, &channels, 0);
		}
		stbi_flip_vertically_on_write(1);
		stbi_write_png(filepath->c_str(), width, height, channels, data, width * channels);
		break;
	}
}

void UI::OnUpdate()
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
}
