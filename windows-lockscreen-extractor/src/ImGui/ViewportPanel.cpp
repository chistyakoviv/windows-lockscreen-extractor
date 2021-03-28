#include "ViewportPanel.h"

void ViewportPanel::render()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGuiWindowFlags window_flags = 0;
	//window_flags |= ImGuiWindowFlags_NoTitleBar;
	//window_flags |= ImGuiWindowFlags_MenuBar;
	//window_flags |= ImGuiWindowFlags_NoMove;
	//window_flags |= ImGuiWindowFlags_NoResize;
	//window_flags |= ImGuiWindowFlags_NoCollapse;
	//window_flags |= ImGuiWindowFlags_NoNav;
	//window_flags |= ImGuiWindowFlags_NoBackground;
	//window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//window_flags |= ImGuiWindowFlags_NoDocking;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport", nullptr, window_flags);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

	ImTextureID texId = io.Fonts->TexID;
	ImVec2 uvMin = ImVec2(0.0f, 1.0f); // Top-left
	ImVec2 uvMax = ImVec2(1.0f, 0.0f); // Lower-right

	if (m_TextureID)
		ImGui::Image((void*)m_TextureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, uvMin, uvMax);

	ImGui::End();
	ImGui::PopStyleVar();
}

std::pair<int32_t, int32_t> ViewportPanel::GetViewportSize() const
{
	int32_t width = m_ViewportSize.x;
	int32_t height = m_ViewportSize.y;
	return { width, height };
}

void ViewportPanel::SetTextureID(uint32_t textureID)
{
	m_TextureID = textureID;
}
