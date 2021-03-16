#include "FileSystem.h"

#include <clocale>
#include <locale>
#include <codecvt>

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

#include <iostream>

#include <Stringapiset.h>

static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> s_Converter;

std::vector<std::string> FileSystem::ReadDir(const std::string& dirpath)
{
	std::vector<std::string> files;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t lengthOfPath;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	std::wstring convertedDirpath = s_Converter.from_bytes(dirpath);

	// Check that the input path plus 3 is not longer than MAX_PATH.
	// Three characters are for the "\*" plus NULL appended below.
	StringCchLength(convertedDirpath.c_str(), MAX_PATH, &lengthOfPath);

	if (lengthOfPath > (MAX_PATH - 3))
	{
		return {};
	}

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.
	StringCchCopy(szDir, MAX_PATH, convertedDirpath.c_str());
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return {};
	}

	// Gather all the files in the directory.
	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			std::string fileName = s_Converter.to_bytes(ffd.cFileName);
			files.push_back(fileName);
		}
	}    while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		return {};
	}

	FindClose(hFind);
	return files;
}

bool FileSystem::CopyFileX(std::string& source, std::wstring& dest)
{
	std::wstring convertedSource = s_Converter.from_bytes(source);
	return CopyFile(convertedSource.c_str(), dest.c_str(), TRUE);
}
