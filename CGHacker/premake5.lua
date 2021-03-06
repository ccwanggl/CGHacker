project "CGHacker"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"


    targetdir ("..bin/" .. outputdir .. "/%{prj.name}")
    objdir ("..bin-int/" .. outputdir .. "/%{prj.name}")

-- not use precompiled header

    pchheader "cgpch.h"
    pchsource "%{wks.location}/CGHacker/src/cgpch.cpp"

    files 
    {
        "%{wks.location}/CGHacker/src/CGHacker/**.h",
        "%{wks.location}/CGHacker/src/CGHacker/**.cpp",
        "%{wks.location}/CGHacker/src/cg.h",
        "%{wks.location}/CGHacker/src/cgpch.h",
        "%{wks.location}/CGHacker/src/cgpch.cpp",
    }


    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "NMROS_ENABLE_ASSERT",
    }

    includedirs
    {
        "src", 
        "vendor/spdlog/include",
        "vendor/eigen/Eigen",
        "%{IncludeDir.GLFW}",
    }

    links 
    {
        "GLFW",
        "opengl32.lib"
    }

    libdirs
    {
        --"vendor/JAI/lib/Win64_x64",
        --"vendor/NI/lib64/msvc",
        --"vendor/art/PCI9757/libs"
    }

    --filter "files:**.c"
    --    flags {"NoPCH"}

    filter "system:windows"
        systemversion "latest"

        defines 
        {
        }

    filter "configurations:Debug"
        defines "CG_DEBUG"
        runtime "Debug"
        symbols "on"
        staticruntime "off"

    filter "configurations:Release"
        defines "CG_RELEASE"
        runtime "Release"
        optimize "on"
        staticruntime "on"

    filter "configurations:Dist"
        defines "CG_DIST"
        runtime "Release"
        optimize "on"
        staticruntime "on"