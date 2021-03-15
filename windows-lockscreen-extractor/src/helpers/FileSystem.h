#pragma once

#include <vector>
#include <string>

class FileSystem
{
public:
	static std::vector<std::string> ReadDir(const std::string& dirpath);
	static bool CopyFileX(std::string& source, std::string& dest);
};
