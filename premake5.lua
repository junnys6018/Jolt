workspace "Jolt"
	architecture "x64"
	configurations {"Debug", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

-- Jolt
project "Jolt"
	location "Jolt"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/GLFW/include/GLFW/*.h"
	}

	includedirs 
	{
		"Jolt/src",
		"Jolt/vendor/GLM",
		"Jolt/vendor/stb_image/src",
		"Jolt/vendor/GLFW/include",
		"Jolt/vendor/imgui",
		"Jolt/vendor/GLAD/include",
		"Jolt/vendor/spdlog/include"
	}

	links 
	{
		"stb_image",
		"ImGui",
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	pchheader "pch.h"
	pchsource "Jolt/src/pch.cpp"

	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "configurations:Debug"
		defines { "JOLT_DEBUG", "JOLT_PROFILE" }
		symbols "On"

	filter "configurations:Release"
		defines { "JOLT_RELEASE", "JOLT_PROFILE" }
		optimize "On"


-- Dependencies
group "Dependencies"

include "Jolt/vendor/GLFW"
include "Jolt/vendor/imgui"
include "Jolt/vendor/stb_image"
include "Jolt/vendor/GLAD"
	
group ""	
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs 
	{
		"Jolt/src",
		
		"Jolt/vendor/GLFW/include",
		"Jolt/vendor/GLM",
		"Jolt/vendor/imgui",
		"Jolt/vendor/GLAD/include",
		"Jolt/vendor/spdlog/include"
	}

	links
	{
		"Jolt"
	}

	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "configurations:Debug"
		defines { "JOLT_DEBUG", "JOLT_PROFILE" }
		symbols "On"

	filter "configurations:Release"
		defines { "JOLT_RELEASE", "JOLT_PROFILE" }
		optimize "On"