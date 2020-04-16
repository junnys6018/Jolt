project "Sandbox"
	location ""
	kind "ConsoleApp"
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
		"../Jolt/src",
		
		"../Jolt/vendor/GLFW/include",
		"../Jolt/vendor/GLM",
		"../Jolt/vendor/imgui",
		"../Jolt/vendor/GLAD/include",
		"../Jolt/vendor/spdlog/include"
	}

	links
	{
		"Jolt",
		"stb_image",
		"ImGui",
		"GLFW",
		"Glad",
	}

	filter "configurations:Debug"
		defines { "JOLT_DEBUG", "JOLT_PROFILE" }
		symbols "On"

	filter "configurations:Distribution"
		defines { "JOLT_DISTRIBUTION", "JOLT_PROFILE" }
		optimize "On"

	filter "configurations:Release"
		defines { "JOLT_RELEASE" }
		optimize "On"

	filter "system:windows"
	
		postbuildcommands
		{
			"copy %{wks.location}bin\\" .. outputdir .. "\\%{prj.name}\\%{prj.name}.exe %{prj.location}%{prj.name}.exe"
		}
		defines { "_CRT_SECURE_NO_WARNINGS" }
		
	filter "system:linux"
		postbuildcommands
		{
			"@echo cp %{wks.location}/bin/" .. outputdir .. "/%{prj.name}/%{prj.name} %{prj.location}/%{prj.name}.out",
			"@cp %{wks.location}/bin/" .. outputdir .. "/%{prj.name}/%{prj.name} %{prj.location}/%{prj.name}.out"
		}
		links { "dl", "pthread" }