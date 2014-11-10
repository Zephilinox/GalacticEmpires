Galactic Empires
================

A Sci-Fi 4x Game

License
=======

Licensed under "Attribution-NonCommercial 4.0 International", view the LICENSE.txt file for full details
You can view a simplified summary at http://creativecommons.org/licenses/by-nc-sa/4.0/

Building
========

* Download & install premake (version 4.4 beta 5 was used)
* Run "premake4 --help" to view a list of build options.
* Run one of them (e.g. "premake4 codeblocks") in the same directory as the premake4.lua file.
* Run your build in the builds/ directory

You may need to compile and build the appropriate libraries for your system. View extlibs/mingw/ for an example.

For linux it is assumed that you have the libraries installed on your system

Libraries
=========

* SFML 2.1
 * Windowing and Graphics API 
* SFGUI 0.2.0
 * GUI API
* INIParser
 * INI Reading and Writing
* Thor
 * High-level functionality for SFML
* Aurora
 * Required by Thor
* Lua 5.2.3
 * Scripting and data storage
* LuaBridge
 * Aids in accessing the Lua Stack