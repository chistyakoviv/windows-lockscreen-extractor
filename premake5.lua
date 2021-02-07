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

group "Dependencies"
	include "vendor/premake"
group ""

include "windows-lockscreen-extractor"
