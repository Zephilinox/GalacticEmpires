require "os_copydir"

solution "GalacticEmpires"
	configurations {"Debug", "Release"}
	location ("builds/".._ACTION)
	
	project "GalacticEmpires"
		location ("builds/".._ACTION)
		objdir ("builds/".._ACTION.."/obj")
		language "C++"
		files {"main.cpp", "include/**.hpp", "src/**.cpp", "extlibs/INIParser/include/**.hpp", "extlibs/INIParser/src/**.cpp"}
		includedirs {"include", "extlibs/SFML/include", "extlibs/SFGUI/include", "extlibs/LuaBridge/include", "extlibs/INIParser/include", os.findlib("lua5.2")}
		libdirs {"extlibs/SFML/lib", "extlibs/SFGUI/lib"}
		defines {"SFML_STATIC", "SFGUI_STATIC"}
		links {"lua", "sfgui-s"}
		linkoptions {"-static", "-static-libgcc", "-static-libstdc++"}
		buildoptions "-std=c++11"
		os.copydir("data", "builds/".._ACTION.."/data")
		
		configuration "Debug"
			kind "ConsoleApp"
			targetdir ("builds/".._ACTION.."/bin/Debug/")
			defines {"DEBUG"}
			flags {"Symbols"}
			links {"sfml-graphics-s-d", "sfml-window-s-d", "sfml-system-s-d"}
 
		configuration "Release"
			kind "WindowedApp"
			targetdir ("builds/".._ACTION.."/bin/Release/")
			defines {"NDEBUG"}
			flags {"Optimize"}
			links {"sfml-graphics-s", "sfml-window-s", "sfml-system-s"}
			