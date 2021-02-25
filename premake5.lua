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


-- projects
group "Dependencies"
	include "vendor"
group ""


include "CGHacker"
include "CGHackerTest"