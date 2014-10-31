require "os_copydir"

local compiler = ""

if _ACTION == "codeblocks" or _ACTION == "codelite" then
	compiler = "mingw"
elseif _ACTION == "vs2010" or _ACTION == "vs2008" or _ACTION == "vs2005" or _ACTION == "vs2003" or _ACTION == "vs20002" then
	compiler = "msvc"
elseif _ACTION == "gmake" then
	compiler = "linux"
elseif _ACTION == "xcode3" then
	compiler = "mac"
else
	print("Unknown compiler or system")
end

solution "GalacticEmpires"
	configurations {"Debug", "Release"}
	location ("builds/".._ACTION)
	
	project "GalacticEmpires"
		location ("builds/".._ACTION)
		objdir ("builds/".._ACTION.."/obj")
		language "C++"
		files {"main.cpp", "include/**.hpp", "src/**.cpp"}
		includedirs {"include", "extlibs/headers/SFML/include", "extlibs/headers/SFGUI/include", "extlibs/headers/INIParser/include"}
		libdirs {"builds/".._ACTION.."/dll", "extlibs/"..compiler.."/SFML/lib", "extlibs/"..compiler.."/SFGUI/lib"}
		--defines {"SFML_STATIC", "SFGUI_STATIC"}
		links {"sfgui"}
		linkoptions {"-static", "-static-libgcc", "-static-libstdc++"}
		buildoptions "-std=c++11"
		os.copydir("data", "builds/".._ACTION.."/data")
		os.copydir("extlibs/"..compiler.."/SFML/bin", "builds/".._ACTION.."/dll")
		os.copydir("extlibs/"..compiler.."/SFGUI/bin", "builds/".._ACTION.."/dll")
		
		configuration "Debug"
			kind "ConsoleApp"
			targetdir ("builds/".._ACTION.."/bin/Debug/")
			defines {"DEBUG"}
			flags {"Symbols"}
			links {"sfml-graphics-d", "sfml-window-d", "sfml-system-d"}

		configuration "Release"
			kind "WindowedApp"
			targetdir ("builds/".._ACTION.."/bin/Release/")
			defines {"NDEBUG"}
			flags {"Optimize"}
			links {"sfml-graphics", "sfml-window", "sfml-system"}
			