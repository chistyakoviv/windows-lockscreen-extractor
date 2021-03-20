#pragma once

#include <vector>
#include <string>

class FileSystem
{
public:
	static std::vector<std::wstring> ReadDir(const std::wstring& dirpath);
	static bool CopyFileX(std::wstring& source, std::wstring& dest);
};
