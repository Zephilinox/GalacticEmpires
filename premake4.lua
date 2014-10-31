require "os_copydir"

local system = os.get()
local compiler = ""

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

print("system = "..system)
print("compiler = "..compiler)

solution "GalacticEmpires"
	configurations {"Debug", "Release"}
	location ("builds/".._ACTION)
	
	project "GalacticEmpires"
		location ("builds/".._ACTION)
		objdir ("builds/".._ACTION.."/obj")
		language "C++"
		files {"main.cpp", "include/**.hpp", "src/**.cpp"}
		
		if system == "windows" then
			includedirs {"include", "extlibs/headers/SFML/include", "extlibs/headers/SFGUI/include", "extlibs/headers/INIParser/include"}
			libdirs {"builds/".._ACTION.."/dll", "extlibs/"..compiler.."/SFML/lib", "extlibs/"..compiler.."/SFGUI/lib"}
		else
			includedirs {"include", "extlibs/headers/INIParser/include"}
			libdirs {"builds/".._ACTION.."/dll"}
		end
		
		linkoptions {"-static", "-static-libgcc", "-static-libstdc++"}
		buildoptions "-std=c++11"
		os.copydir("data", "builds/".._ACTION.."/data")
		
		if system == "windows" then
			os.copydir("extlibs/"..compiler.."/SFML/bin", "builds/".._ACTION.."/dll")
			os.copydir("extlibs/"..compiler.."/SFGUI/bin", "builds/".._ACTION.."/dll")
		end
		
		configuration "Debug"
			kind "ConsoleApp"
			targetdir ("builds/".._ACTION.."/bin/Debug/")
			defines {"DEBUG"}
			flags {"Symbols"}
			
			if system == "windows" then
				defines {"SFML_STATIC", "SFGUI_STATIC"}
				links {"sfgui-s", "sfml-graphics-s-d", "sfml-window-s-d", "sfml-system-s-d"}
			else 
				links {"sfgui", "sfml-graphics-d", "sfml-window", "sfml-system"}
			end

		configuration "Release"
			kind "WindowedApp"
			targetdir ("builds/".._ACTION.."/bin/Release/")
			defines {"NDEBUG"}
			flags {"Optimize"}
			links {"sfgui", "sfml-graphics", "sfml-window", "sfml-system"}
			