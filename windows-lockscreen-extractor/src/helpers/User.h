#pragma once

#include <string>

class User
{
public:
	static std::wstring GetProfileDir();
	static std::wstring GetLockScreenImagesDir();
	static std::wstring GetLockScreenImageAbsolutePath(const std::wstring& imageName);
};
