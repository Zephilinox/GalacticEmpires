-- A solution contains projects, and defines the available configurations
solution "GalacticEmpires"
	configurations {"Debug", "Release"}
	location ("builds/".._ACTION)
	
	-- A project defines one build target
	project "GalacticEmpires"
		location ("builds/".._ACTION)
		objdir ("builds/".._ACTION.."/obj")
		language "C++"
		files {"main.cpp", "include/**.hpp", "src/**.cpp"}
		includedirs {"include", "extlibs/SFML/include", "extlibs/SFGUI/include", "extlibs/LuaBridge/include"}
		libdirs {"extlibs/SFML/lib", "extlibs/SFGUI/lib"}
		defines {"SFML_STATIC", "SFGUI_STATIC"}
		links {"lua", "sfgui-s"}
		linkoptions {"-static", "-static-libgcc", "-static-libstdc++"}
		buildoptions "-std=c++11"
		
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