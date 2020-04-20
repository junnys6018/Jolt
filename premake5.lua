workspace "Jolt"
	architecture "x64"
	configurations {"Debug", "Distribution", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

-- Jolt Core --
group "Core Library"

include "Jolt"
include "Util"

-- Dependencies --
group "Dependencies"

include "Jolt/vendor/GLFW"
include "Jolt/vendor/ImGui"
include "Jolt/vendor/stb_image"
include "Jolt/vendor/GLAD"

-- Demos --
group "Examples"

include "Sandbox"