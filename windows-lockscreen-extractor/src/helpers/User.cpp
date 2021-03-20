#include "User.h"

#include <clocale>
#include <locale>
#include <codecvt>

static const wchar_t* LOCK_SCREEN_IMAGES_PATH = L"\\AppData\\Local\\Packages\\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\\LocalState\\Assets";

static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> s_Converter;

std::wstring User::GetProfileDir()
{
	return s_Converter.from_bytes(getenv("USERPROFILE"));
}

std::wstring User::GetLockScreenImagesDir()
{
	return User::GetProfileDir() + LOCK_SCREEN_IMAGES_PATH;
}

std::wstring User::GetLockScreenImageAbsolutePath(const std::wstring& imageName)
{
	return User::GetLockScreenImagesDir() + L"\\" + imageName;
}
