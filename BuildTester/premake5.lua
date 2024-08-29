workspace "BuildTester"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

    -- Workspace-wide build options for MSVC
    filter "system:windows"
    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include "Tester"
    include "Walnut/Build-Walnut-External.lua"
