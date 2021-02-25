project "ImGui"
	language "C++"
	kind "StaticLib"
	cppdialect "C++17"
	staticruntime "on"
	systemversion "latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- libdirs
	-- {
	--	"bin/" .. outputdir .. "/%{prj.name}"
	-- }

	files
	{
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp",
        "imgui_tables.cpp",
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_opengl3.h",
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
