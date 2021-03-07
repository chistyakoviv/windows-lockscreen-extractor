#include "FileSystem.h"

#include <clocale>
#include <locale>
#include <codecvt>

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

static std::string narrow(std::wstring const& text)
{
	std::locale const loc("");
	wchar_t const* from = text.c_str();
	std::size_t const len = text.size();
	std::vector<char> buffer(len + 1);
	std::use_facet<std::ctype<wchar_t> >(loc).narrow(from, from + len, '_', &buffer[0]);
	return std::string(&buffer[0], &buffer[len]);
}

std::vector<std::string > FileSystem::ReadDir(const std::string& dirpath)
{
	std::vector<std::string > files;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	std::wstring converted_dirpath = converter.from_bytes(dirpath);

	// Check that the input path plus 3 is not longer than MAX_PATH.
	// Three characters are for the "\*" plus NULL appended below.

	StringCchLength(converted_dirpath.c_str(), MAX_PATH, &length_of_arg);

	if (length_of_arg > (MAX_PATH - 3))
	{
		return {};
	}

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.

	StringCchCopy(szDir, MAX_PATH, converted_dirpath.c_str());
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return {};
	}

	// List all the files in the directory with some info about them.

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

		}
		else
		{
			std::string fileName = converter.to_bytes(ffd.cFileName);
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
