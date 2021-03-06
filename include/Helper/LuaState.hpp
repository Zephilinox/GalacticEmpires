#ifndef LUASTATE_HPP
#define LUASTATE_HPP

#include <iostream>
#include <vector>

#include <lua5.2/lua.hpp>
#include <LuaBridge/LuaBridge.h>

//This is called from within Lua in order to print the stack trace
static int traceback(lua_State* L)
{
    const char *msg = lua_tostring(L, 1);
    //fprintf(stderr, "Traceback msg: %s\n", msg); //cout breaks function
    if (msg)
    {
        luaL_traceback(L, L, msg, 1);
    }
    else if (!lua_isnoneornil(L, 1))
    {
        if (!luaL_callmeta(L, 1, "__tostring"))
        {
            lua_pushliteral(L, "(no error message)");
        }
    }

    return 1;
}

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
    lua_State* m_luaState;
};

#endif //LUASTATE_HPP
