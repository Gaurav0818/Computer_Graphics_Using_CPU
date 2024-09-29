workspace "Computer_Graphics_Using_CPU"
    architecture "x64"
    startproject "Computer_Graphics"

    configurations
    {
        "Debug",
        "Release"
    }

project "Computer_Graphics"
    kind "ConsoleApp"
    language "C++"
    cppdialect  "C++20"
    systemversion "latest"

    targetdir "temp/bin/%{cfg.buildfg}-Build"
    objdir "temp/obj/%{cfg.buildfg}"

    files
    {
        "src/public/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src/public/",
        "vendor/SDL2/include/"
    }

    libdirs
    {
        "vendor/SDL2/lib/"
    }

    links
    {
        "SDL2.lib",
        "SDL2main.lib"
    }

