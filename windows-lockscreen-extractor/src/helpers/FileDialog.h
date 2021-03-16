#pragma once

#include <string>
#include <optional>
#include <GLFW/glfw3.h>

class FileDialogs
{
public:
	static std::optional<std::wstring> SaveFile(GLFWwindow* window, const wchar_t* filter);
};
