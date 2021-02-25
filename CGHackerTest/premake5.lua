project "CGHackerTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"


	targetdir ("..bin/" .. outputdir .. "/%{prj.name}")
	objdir ("..bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
    }
    
    includedirs
	{
		"%{wks.location}/CGHacker/vendor/spdlog/include",
        "%{wks.location}/CGHacker/vendor/eigen",
		"%{wks.location}/CGHacker/src",
        "%{IncludeDir.GLFW}",
    }
    
    links
    {
        "GLFW",
        "opengl32.lib"
    }

    libdirs
    {
        
    }
    
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