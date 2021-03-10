#include "Application.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main()
{
	Application* app = new Application();

	app->Run();
}
