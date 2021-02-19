project "windows-lockscreen-extractor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glfw}",
	}

	links
	{
		"opengl32.lib",
		"Glad",
		"glfw"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "WLE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "WLE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "WLE_DIST"
		runtime "Release"
		optimize "on"
