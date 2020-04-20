project "Util"
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

filter "system:windows"
    postbuildcommands
    {
        "copy %{wks.location}bin\\" .. outputdir .. "\\%{prj.name}\\%{prj.name}.exe %{prj.location}Jolt.exe"
    }
    defines { "_CRT_SECURE_NO_WARNINGS" }

filter "system:linux"
    postbuildcommands
    {
        "@echo cp %{wks.location}/bin/" .. outputdir .. "/%{prj.name}/%{prj.name} %{prj.location}/Jolt.out",
        "@cp %{wks.location}/bin/" .. outputdir .. "/%{prj.name}/%{prj.name} %{prj.location}/Jolt.out"
    }
    
filter "system:linux"
    links { "pthread" }

filter "configurations:Debug"
    symbols "On"

filter "configurations:Distribution"
    symbols "On"

filter "configurations:Release"
    optimize "On"

