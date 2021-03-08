#include "ViewportPanel.h"

void ViewportPanel::render()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoNav;
	//window_flags |= ImGuiWindowFlags_NoBackground;
	//window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//window_flags |= ImGuiWindowFlags_NoDocking;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport", nullptr, window_flags);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

	ImTextureID texId = io.Fonts->TexID;
	ImVec2 uvMin = ImVec2(0.0f, 0.0f); // Top-left
	ImVec2 uvMax = ImVec2(1.0f, 1.0f); // Lower-right

	ImGui::Image(texId, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, uvMin, uvMax);
	ImGui::End();
	ImGui::PopStyleVar();
}
