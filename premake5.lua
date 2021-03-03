include "./vendor/premake_customization/solution_items.lua"

workspace "CGHacker"
    architecture "x64"
    startproject "CGHackerTest"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

	solution_items
	{
		".editorconfig"
	}

    flags
    {
            "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["eigen"]   = "vendor/eigen/Eigen"
IncludeDir["GLFW"]    = "%{wks.location}/CGHacker/vendor/glfw/include"
IncludeDir["GLAD"]    = "%{wks.location}/CGHacker/vendor/Glad/include"


-- projects
group "Dependencies"
	include "vendor"
    include "CGHacker/vendor/glfw"
    include "CGHacker/vendor/Glad"
group ""


include "CGHacker"
include "CGHackerTest"

include "premakes/learn_opengl.lua"