#include "User.h"

static const char* LOCK_SCREEN_IMAGES_PATH = "\\AppData\\Local\\Packages\\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\\LocalState\\Assets";

std::string User::GetProfileDir()
{
	return getenv("USERPROFILE");
}

std::string User::GetLockScreenImagesDir()
{
	return User::GetProfileDir() + LOCK_SCREEN_IMAGES_PATH;
}
