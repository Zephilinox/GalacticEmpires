#ifndef LUASTATE_HPP
#define LUASTATE_HPP

#include <iostream>
#include <vector>

#include <lua5.2/lua.hpp>
#include <LuaBridge/LuaBridge.h>

class LuaState
{
public:
    LuaState();
    ~LuaState();

    int loadFile(const std::string& file);
    int execute();

    luabridge::LuaRef getGlobal(const std::string& varName);

    lua_State* getRawState();

private:
	static int traceback(lua_State* L); //This is called from within Lua in order to print the stack trace

    lua_State* m_luaState;
};

#endif //LUASTATE_HPP
