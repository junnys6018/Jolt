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
	}

	includedirs 
	{
		"Jolt/vendor/stb_image/src",
		"Jolt/vendor/GLFW/include",
		"Jolt/vendor/imgui",
		"Jolt/vendor/GLAD/include"
	}

	links 
	{
		"stb_image",
		"ImGui",
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
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
		"Jolt/src/"
	}

	links
	{
		"Jolt"
	}

	filter "configurations:Debug"
	defines { "DEBUG" }
	symbols "On"

	filter "configurations:Release"
	defines { "NDEBUG" }
	optimize "On"