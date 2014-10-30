-- A solution contains projects, and defines the available configurations
solution "GalacticEmpires"
	configurations {"Debug", "Release"}
	location "build"
	
	-- A project defines one build target
	project "GalacticEmpires"
		language "C++"
		files {"main.cpp", "include/**.hpp", "src/**.cpp"}
		includedirs {"include", "extlibs/SFML/include", "extlibs/SFGUI/include", "extlibs/LuaBridge/include"}
		libdirs {"extlibs/SFML/lib", "extlibs/SFGUI/lib"}
		defines {"SFML_STATIC", "SFGUI_STATIC"}
		links {"liblua", "sfgui"}
		buildoptions "-std=c++11"
		
		configuration "Debug"
			kind "ConsoleApp"
			defines {"DEBUG"}
			flags {"Symbols"}
			links {"sfml-graphics-s-d", "sfml-window-s-d", "sfml-system-s-d"}
 
		configuration "Release"
			kind "WindowedApp"
			defines {"NDEBUG"}
			flags {"Optimize"}
			links {"sfml-graphics-s", "sfml-window-s", "sfml-system-s"}