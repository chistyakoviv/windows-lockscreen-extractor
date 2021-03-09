workspace "windows-lockscreen-extractor"
	architecture "x64"
	startproject "windows-lockscreen-extractor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "%{wks.location}/windows-lockscreen-extractor/vendor/Glad/include"
IncludeDir["GLFW"] = "%{wks.location}/windows-lockscreen-extractor/vendor/GLFW/include"
IncludeDir["ImGui"] = "%{wks.location}/windows-lockscreen-extractor/vendor/ImGui"
IncludeDir["stb_image"] = "%{wks.location}/windows-lockscreen-extractor/vendor/stb_image"

group "Dependencies"
	include "vendor/premake"
	include "windows-lockscreen-extractor/vendor/Glad"
	include "windows-lockscreen-extractor/vendor/GLFW"
	include "windows-lockscreen-extractor/vendor/ImGui"
group ""

include "windows-lockscreen-extractor"
