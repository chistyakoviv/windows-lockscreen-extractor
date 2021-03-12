#pragma once

#include <string>
#include <optional>
#include <GLFW/glfw3.h>

class FileDialogs
{
public:
	static std::optional<std::string> SaveFile(GLFWwindow* window, const char* filter);
};
