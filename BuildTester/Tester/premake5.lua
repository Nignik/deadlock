project "Tester"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files {
        "src/**.cpp", "src/**.h"
    }

    includedirs
    {
      "%{wks.location}/Walnut/vendor/imgui",
      "%{wks.location}/Walnut/vendor/glfw/include",

      "%{wks.location}/Walnut/Walnut/Source",
      "%{wks.location}/Walnut/Walnut/Platform/GUI",

      "%{IncludeDir.VulkanSDK}",
      "%{IncludeDir.glm}",
    }

   links
    {
        "Walnut"
    }

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      defines { "WL_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "WL_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"