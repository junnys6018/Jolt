workspace "Jolt"
	architecture "x64"
	configurations {"Debug", "Distribution", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

-- Jolt
project "Jolt"
	location "Jolt"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17" 

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
		"Jolt/vendor/ImGui",
		"Jolt/vendor/GLAD/include",
		"Jolt/vendor/spdlog/include"
	}

	links 
	{
		"stb_image",
		"ImGui",
		"GLFW",
		"Glad",
	}

	pchheader "pch.h"
	pchsource "Jolt/src/pch.cpp"

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



-- Dependencies
group "Dependencies"

include "Jolt/vendor/GLFW"
include "Jolt/vendor/ImGui"
include "Jolt/vendor/stb_image"
include "Jolt/vendor/GLAD"
	
group "Examples"

include "Sandbox"

group ""
		
project "Util"
	location "Util"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17" 

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	filter "system:windows"
		postbuildcommands
		{
			"copy %{wks.location}bin\\" .. outputdir .. "\\%{prj.name}\\%{prj.name}.exe %{prj.location}Jolt.exe"
		}

		defines { "_CRT_SECURE_NO_WARNINGS" }
		
	filter "system:linux"
		links { "pthread" }

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Distribution"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

