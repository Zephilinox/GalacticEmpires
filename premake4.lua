require "os_copydir" --usermade function to copy a directory

local system = os.get()
local build_tool = ""

--determine what is being used to compile and if that is supported
--environment is used to determine which subfolder of extlibs to use when looking for libraries
if system == "windows" then
    if _ACTION == "codeblocks" or _ACTION == "codelite" or _ACTION == "gmake" then
        environment = "mingw"
    elseif _ACTION == "vs2010" or _ACTION == "vs2008" or _ACTION == "vs2005" or _ACTION == "vs2003" or _ACTION == "vs20002" then
        environment = "msvc"
    else
        print("Using '".._ACTION.."' on '"..system.."' is not supported")
        os.exit();
    end    
elseif system == "macosx" then
    if _ACTION == "xcode3" then
        environment = "mac"
    else
        print("Using '".._ACTION.."' on '"..system.."' is not supported")
        os.exit();
    end
elseif system == "linux" or system == "bsd" or system == "solaris" then
    if _ACTION == "codeblocks" or _ACTION == "codelite" or _ACTION == "gmake" then
        environment = "linux"
    else
        print("Using '".._ACTION.."' on '"..system.."' is not supported")
        os.exit();
    end
else
    print("Unknown system '"..system.."'")
    os.exit();
end

print("system = "..system)
print("environment = "..environment)

local include_dirs_libs = {
"extlibs/headers/SFML/include",
"extlibs/headers/Thor/include",
"extlibs/headers/Lua/include",
"extlibs/headers/CEGUI/include",
}

local include_dirs_header_only = {
"include",
"extlibs/headers/Aurora/include",
"extlibs/headers/LuaBridge/include",
"extlibs/headers/INIParser/include",
"extlibs/headers/Flowger/include"
}

local libs = {
"extlibs/"..environment.."/SFML/lib",
"extlibs/"..environment.."/Thor/lib",
"extlibs/"..environment.."/Lua/lib",
"extlibs/"..environment.."/CEGUI/lib"
}

local cegui_dlls = {
"CEGUIBase-0",
"CEGUIExpatParser",
"CEGUIOpenGLRenderer-0",
"CEGUISILLYImageCodec",
"freetype",
"pcre",
"SILLY",
"zlib",
"jpeg",
"glew",
"expat",
"png"
}

--copy data folder to build and bin folders
print("copying data files")
os.copydir("data", "builds/".._ACTION.."/data")
os.copydir("data", "builds/".._ACTION.."/bin/Debug/data")
os.copydir("data", "builds/".._ACTION.."/bin/Release/data") 

--For windows we will want to copy over the .dll's of libraries to the dll folder, e.g. builds/codeblocks/dll
if system == "windows" then
    print("copying DLL files")
    os.mkdir("builds/".._ACTION.."/dll/")
    
    os.copyfile("extlibs/"..environment.."/SFML/bin/openal32.dll", "builds/".._ACTION.."/dll/openal32.dll")
    os.copyfile("extlibs/"..environment.."/SFML/bin/libsndfile-1.dll", "builds/".._ACTION.."/dll/libsndfile-1.dll")
	
	--MSVC CEGUI does not utilise 'lib' prefix, mingw does.
	for k, v in ipairs(cegui_dlls) do
		if environment == "mingw" then
			if v == "png" then --mingw CEGUI has png as liblibpng.dll, we need it to be png.dll
				os.copyfile("extlibs/"..environment.."/CEGUI/bin/liblib"..v.."_d.dll", "builds/".._ACTION.."/dll/"..v.."_d.dll")
				os.copyfile("extlibs/"..environment.."/CEGUI/bin/liblib"..v..".dll", "builds/".._ACTION.."/dll/"..v..".dll")
			elseif v == "expat" then --mingw CEGUI has expat as libexpat.dll, we need it to be expat.dll
				os.copyfile("extlibs/"..environment.."/CEGUI/bin/lib"..v.."_d.dll", "builds/".._ACTION.."/dll/"..v.."_d.dll")
				os.copyfile("extlibs/"..environment.."/CEGUI/bin/lib"..v..".dll", "builds/".._ACTION.."/dll/"..v..".dll")
			else
				os.copyfile("extlibs/"..environment.."/CEGUI/bin/lib"..v.."_d.dll", "builds/".._ACTION.."/dll/lib"..v.."_d.dll")
				os.copyfile("extlibs/"..environment.."/CEGUI/bin/lib"..v..".dll", "builds/".._ACTION.."/dll/lib"..v..".dll")
			end
		else
			os.copyfile("extlibs/"..environment.."/CEGUI/bin/"..v.."_d.dll", "builds/".._ACTION.."/dll/"..v.."_d.dll")
			os.copyfile("extlibs/"..environment.."/CEGUI/bin/"..v..".dll", "builds/".._ACTION.."/dll/"..v..".dll")
		end
	end
	
	--MSVC CEGUI requires minizip
	if environment == "msvc" then
		os.copyfile("extlibs/"..environment.."/CEGUI/bin/minizip_d.dll", "builds/".._ACTION.."/dll/minizip_d.dll")
		os.copyfile("extlibs/"..environment.."/CEGUI/bin/minizip.dll", "builds/".._ACTION.."/dll/minizip.dll")
	end
	
	--[[
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libCEGUIBase-0_d.dll", "builds/".._ACTION.."/dll/libCEGUIBase-0_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libCEGUIExpatParser_d.dll", "builds/".._ACTION.."/dll/libCEGUIExpatParser_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libCEGUIOpenGLRenderer-0_d.dll", "builds/".._ACTION.."/dll/libCEGUIOpenGLRenderer-0_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libCEGUISILLYImageCodec_d.dll", "builds/".._ACTION.."/dll/libCEGUISILLYImageCodec_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libfreetype_d.dll", "builds/".._ACTION.."/dll/libfreetype_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libpcre_d.dll", "builds/".._ACTION.."/dll/libpcre_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libSILLY_d.dll", "builds/".._ACTION.."/dll/libSILLY_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libzlib_d.dll", "builds/".._ACTION.."/dll/libzlib_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libjpeg_d.dll", "builds/".._ACTION.."/dll/libjpeg_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libglew_d.dll", "builds/".._ACTION.."/dll/libglew_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libexpat_d.dll", "builds/".._ACTION.."/dll/expat_d.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/liblibpng_d.dll", "builds/".._ACTION.."/dll/png_d.dll")
	
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libCEGUIBase-0.dll", "builds/".._ACTION.."/dll/libCEGUIBase-0.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libCEGUIExpatParser.dll", "builds/".._ACTION.."/dll/libCEGUIExpatParser.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libCEGUIOpenGLRenderer-0.dll", "builds/".._ACTION.."/dll/libCEGUIOpenGLRenderer-0.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libCEGUISILLYImageCodec.dll", "builds/".._ACTION.."/dll/libCEGUISILLYImageCodec.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libfreetype.dll", "builds/".._ACTION.."/dll/libfreetype.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libpcre.dll", "builds/".._ACTION.."/dll/libpcre.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libSILLY.dll", "builds/".._ACTION.."/dll/libSILLY.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libzlib.dll", "builds/".._ACTION.."/dll/libzlib.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libjpeg.dll", "builds/".._ACTION.."/dll/libjpeg.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libglew.dll", "builds/".._ACTION.."/dll/libglew.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/libexpat.dll", "builds/".._ACTION.."/dll/expat.dll")
    os.copyfile("extlibs/"..environment.."/CEGUI/bin/liblibpng.dll", "builds/".._ACTION.."/dll/png.dll")
	--]]
	
    os.copydir("builds/".._ACTION.."/dll", "builds/".._ACTION.."/bin/Debug/") --place alongside executable
    os.copydir("builds/".._ACTION.."/dll", "builds/".._ACTION.."/bin/Release/")
end

solution("GalacticEmpires")
    configurations  {"Debug", "Release"}
    location        ("builds/".._ACTION)
    
    project "GalacticEmpires"
        language        ("C++")
        location        ("builds/".._ACTION)
        objdir          ("builds/".._ACTION.."/obj")
        
        files           {"main.cpp", "include/**.hpp", "src/**.cpp"}
		
		if environment == "mingw" or environment == "linux" then
			buildoptions    ("-std=c++11 -Wall -Wextra -Wno-format -Wno-format-extra-args")
		end
        
        includedirs     {include_dirs_header_only}
        libdirs         (libs)
        
        if system == "windows" then
			if environment == "mingw" then
				linkoptions {"-static-libstdc++"}
			end
			
            includedirs (include_dirs_libs)
            libdirs     ("builds/".._ACTION.."/dll")
	elseif system == "linux" then
	    includedirs ("/usr/include/cegui-0")
	    libdirs	("/usr/lib/cegui-0.8")
        end
        
        configuration("Debug")
            kind            ("ConsoleApp")
            defines         {"DEBUG"}
            flags           {"Symbols", "ExtraWarnings"}
            targetdir       ("builds/".._ACTION.."/bin/Debug/")
            
            if system == "windows" then
				if environment == "msvc" then
					buildoptions	("/MTd")
				end
				
                defines     {"SFML_STATIC"}
                links       {"CEGUIBase-0_d", "CEGUIOpenGLRenderer-0_d", "CEGUIExpatParser_d", "CEGUISILLYImageCodec_d", "lua52", "thor-s-d", "sfml-graphics-s-d", "sfml-window-s-d", "sfml-system-s-d"}
            else 
                links       {"lua5.2", "thor", "sfml-graphics", "sfml-window", "sfml-system"}
            end

        configuration("Release")
            kind            ("WindowedApp")
            defines         {"NDEBUG"}
            flags           {"Optimize"}
            targetdir       ("builds/".._ACTION.."/bin/Release/")
            
            if system == "windows" then
				if environment == "msvc" then
					buildoptions	("/MT")
				end
				
                defines     {"SFML_STATIC"}
                links       {"CEGUIBase-0", "CEGUIOpenGLRenderer-0", "CEGUIExpatParser", "CEGUISILLYImageCodec", "lua52", "thor-s", "sfml-graphics-s", "sfml-window-s", "sfml-system-s"}
            else 
                links       {"lua5.2", "thor", "sfml-graphics", "sfml-window", "sfml-system"}
            end
