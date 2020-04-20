project "Jolt"
	location ""
	kind "StaticLib"
	language "C++"
	cppdialect "C++17" 

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs 
	{
		"src",
		"vendor/GLM",
		"vendor/stb_image/src",
		"vendor/GLFW/include",
		"vendor/ImGui",
		"vendor/GLAD/include",
		"vendor/spdlog/include"
	}

	links 
	{
		"stb_image",
		"ImGui",
		"GLFW",
		"Glad",
	}

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	filter "system:windows"
		defines { "_CRT_SECURE_NO_WARNINGS", "PLATFORM_WINDOWS" }

	filter "system:linux"
		defines { "PLATFORM_LINUX" }

	filter "configurations:Debug"
		defines { "JOLT_DEBUG", "JOLT_PROFILE" }
		symbols "On"

	filter "configurations:Distribution"
		defines { "JOLT_DISTRIBUTION", "JOLT_PROFILE" }
		optimize "On"

	filter "configurations:Release"
		defines { "JOLT_RELEASE" }
		optimize "On"
