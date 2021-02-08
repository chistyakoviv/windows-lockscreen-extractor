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

group "Dependencies"
	include "vendor/premake"
	include "windows-lockscreen-extractor/vendor/Glad"
group ""

include "windows-lockscreen-extractor"
