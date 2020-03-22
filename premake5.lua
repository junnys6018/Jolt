workspace "Jolt"
	architecture "x64"
	configurations {"Debug", "Distribution", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

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

	filter "configurations:Distribution"
		defines { "JOLT_DISTRIBUTION", "JOLT_PROFILE" }
		optimize "On"

	filter "configurations:Release"
		defines { "JOLT_RELEASE" }
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
	cppdialect "C++17" 

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

	filter "configurations:Distribution"
		defines { "JOLT_DISTRIBUTION", "JOLT_PROFILE" }
		optimize "On"

	filter "configurations:Release"
		defines { "JOLT_RELEASE" }
		optimize "On"


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

	postbuildcommands
	{
		"copy %{wks.location}bin\\" .. outputdir .. "\\%{prj.name}\\%{prj.name}.exe %{prj.location}%Jolt.exe"
	}

	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Distribution"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

