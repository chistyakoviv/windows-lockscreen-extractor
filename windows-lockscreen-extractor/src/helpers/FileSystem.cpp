#include "FileSystem.h"

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

#include <Stringapiset.h>

std::vector<std::wstring> FileSystem::ReadDir(const std::wstring& dirpath)
{
	std::vector<std::wstring> files;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t lengthOfPath;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	// Check that the input path plus 3 is not longer than MAX_PATH.
	// Three characters are for the "\*" plus NULL appended below.
	StringCchLength(dirpath.c_str(), MAX_PATH, &lengthOfPath);

	if (lengthOfPath > (MAX_PATH - 3))
	{
		return {};
	}

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.
	StringCchCopy(szDir, MAX_PATH, dirpath.c_str());
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
			files.push_back(ffd.cFileName);
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

bool FileSystem::CopyFileX(std::wstring& source, std::wstring& dest)
{
	return CopyFile(source.c_str(), dest.c_str(), TRUE);
}
