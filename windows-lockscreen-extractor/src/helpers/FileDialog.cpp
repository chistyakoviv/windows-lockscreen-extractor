#include "FileDialog.h"

#include <iostream>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

std::optional<std::wstring> FileDialogs::SaveFile(GLFWwindow* window, const wchar_t* filter)
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };
	TCHAR currentDir[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window(window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	if (GetCurrentDirectory(256, currentDir))
		ofn.lpstrInitialDir = currentDir;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

	// Sets the default extension by extracting it from the filter
	ofn.lpstrDefExt = wcschr(filter, '\0') + 1;

	if (GetSaveFileName(&ofn) == TRUE)
		return ofn.lpstrFile;

	return std::nullopt;
}
