require "os_copydir" --usermade function to copy a directory

local system = os.get()
local compiler = ""

--determine what is being used to compile and if that is supported
--compiler is used to determine which subfolder of extlibs to use when looking for libraries
if system == "windows" then
	if _ACTION == "codeblocks" or _ACTION == "codelite" then
		compiler = "mingw"
	elseif _ACTION == "vs2010" or _ACTION == "vs2008" or _ACTION == "vs2005" or _ACTION == "vs2003" or _ACTION == "vs20002" then
		compiler = "msvc"
	else
		print("Using '".._ACTION.."' on '"..system.."' is not supported")
		os.exit();
	end	
elseif system == "macosx" then
	if _ACTION == "xcode3" then
		compiler = "mac"
	else
		print("Using '".._ACTION.."' on '"..system.."' is not supported")
		os.exit();
	end
elseif system == "linux" or system == "bsd" or system == "solaris" then
	if _ACTION == "codeblocks" or _ACTION == "codelite" or _ACTION == "gmake" then
		compiler = "linux"
	else
		print("Using '".._ACTION.."' on '"..system.."' is not supported")
		os.exit();
	end
else
	print("Unknown system '"..system.."'")
	os.exit();
end

--little bit of debug info
print("system = "..system)
print("compiler = "..compiler)

solution "GalacticEmpires"
	configurations {"Debug", "Release"}
	location ("builds/".._ACTION) --e.g. builds/codeblocks/GalacticEmpires.workspace
	
	project "GalacticEmpires"
		location ("builds/".._ACTION) --e.g builds/codeblocks/GalacticEmpires.cbp
		objdir ("builds/".._ACTION.."/obj") --e.g builds/codeblocks/obj/Debug/main.o
		language "C++"
		files {"main.cpp", "include/**.hpp", "src/**.cpp"}
		
		--For windows we want to ensure that we link to the STD statically
		--That we utilise the library headers in extlibs, e.g. extlibs/headers/SFML/include
		--And that we utilise the library lib's, e.g. extlibs/mingw/SFML/lib
		if system == "windows" then
			linkoptions {"-static-libgcc", "-static-libstdc++"}
			includedirs {"include", "extlibs/headers/SFML/include", "extlibs/headers/SFGUI/include", "extlibs/headers/Thor/include", "extlibs/headers/Lua/include", "extlibs/headers/LuaBridge/include", "extlibs/headers/Aurora/include", "extlibs/headers/INIParser/include"}
			libdirs {"builds/".._ACTION.."/dll", "extlibs/"..compiler.."/SFML/lib", "extlibs/"..compiler.."/SFGUI/lib", "extlibs/"..compiler.."/Thor/lib", "extlibs/"..compiler.."/Lua/lib"}
		else
			--For linux (possibly mac) we will link dynamically, therefore we don't need to include any headers or lib's from built libraries.
			includedirs {"include", "extlibs/headers/Aurora/include", "extlibs/headers/Lua/include", "extlibs/headers/LuaBridge/include", "extlibs/headers/INIParser/include"}
		end
		
		buildoptions "-std=c++11"
		os.copydir("data", "builds/".._ACTION.."/data") --copy data such as settings, scripts, images, and audio in to the same dir as the project file, e.g. builds/codeblocks/data
		os.copydir("data", "builds/".._ACTION.."/bin/Debug/data")
		os.copydir("data", "builds/".._ACTION.."/bin/Release/data") 
		
		--For windows we will want to copy over the .dll's of libraries to the dll folder, e.g. builds/codeblocks/dll
		if system == "windows" then
			os.mkdir("builds/".._ACTION.."/dll/")
			--Static is used on windows, so don't copy over every .dll used by libraries
			--os.copydir("extlibs/"..compiler.."/SFML/bin", "builds/".._ACTION.."/dll")
			--os.copydir("extlibs/"..compiler.."/SFGUI/bin", "builds/".._ACTION.."/dll")
			--os.copydir("extlibs/"..compiler.."/Thor/bin", "builds/".._ACTION.."/dll")
			--os.copydir("extlibs/"..compiler.."/Lua/bin", "builds/".._ACTION.."/dll")
			
			os.copyfile("extlibs/"..compiler.."/SFML/bin/openal32.dll", "builds/".._ACTION.."/dll/openal32.dll") --not currently used
			os.copyfile("extlibs/"..compiler.."/SFML/bin/libsndfile-1.dll", "builds/".._ACTION.."/dll/libsndfile-1.dll") --not currently used
			
			os.copydir("builds/".._ACTION.."/dll", "builds/".._ACTION.."/bin/Debug/") --place alongside executable
			os.copydir("builds/".._ACTION.."/dll", "builds/".._ACTION.."/bin/Release/")
		end
		
		configuration "Debug"
			kind "ConsoleApp"
			targetdir ("builds/".._ACTION.."/bin/Debug/") --location for output, e.g. builds/codeblocks/bin/Debug/GalacticEmpires.exe
			defines {"DEBUG"}
			flags {"Symbols", "ExtraWarnings"}
			
			--In windows SFGUI will break itself and SFML, if they aren't static and if they are in debug configuration
			if system == "windows" then
				defines {"SFML_STATIC", "SFGUI_STATIC"}
				links {"lua52", "sfgui-s", "thor-s-d", "sfml-graphics-s-d", "sfml-window-s-d", "sfml-system-s-d"}
			else 
				--Linux has no debug option for SFML
				links {"lua52", "sfgui", "thor", "sfml-graphics", "sfml-window", "sfml-system"}
			end

		configuration "Release"
			kind "WindowedApp"
			targetdir ("builds/".._ACTION.."/bin/Release/") --location for output, e.g. builds/codeblocks/bin/Release/GalacticEmpires.exe
			defines {"NDEBUG"}
			flags {"Optimize"}
			
			--Better to use static in windows to reduce .dll's spamming directory
			if system == "windows" then
				defines {"SFML_STATIC", "SFGUI_STATIC"}
				links {"lua52", "sfgui-s", "thor-s", "sfml-graphics-s", "sfml-window-s", "sfml-system-s"}
			else 
				links {"lua52", "sfgui", "thor", "sfml-graphics", "sfml-window", "sfml-system"}
			end
			
