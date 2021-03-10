#pragma once

#include <string>

class User
{
public:
	static std::string GetProfileDir();
	static std::string GetLockScreenImagesDir();
	static std::string GetLockScreenImageAbsolutePath(const std::string& imageName);
};
