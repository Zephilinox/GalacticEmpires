#include "LuaState.hpp"

//STD
#include <iostream>
#include <string>

//SELF

std::string zge::luaErrorAsString(lua_State* L, int error)
{
    switch (error)
    {
        case LUA_OK:
        {
            return "No Error";
        }

        case LUA_YIELD:
        {
            return "Yield Error";
        }

        case LUA_ERRRUN:
        {
            return std::string("Runtime Error: " + std::string(lua_tostring(L, -1)));
        }

        case LUA_ERRSYNTAX:
        {
            return std::string("Syntax Error: " + std::string(lua_tostring(L, -1)));
        }

        case LUA_ERRMEM:
        {
            return "Memory Allocation Error";
        }

        case LUA_ERRGCMM:
        {
            return "Garbage Collector Error";
        }

        case LUA_ERRERR:
        {
            return "Error Handler Error";
        }

        case LUA_ERRFILE:
        {
            return "File Not Found Error";
        }

        default:
        {
            return std::string("Unknown Lua Error. Code = " + zge::toString(error));
        }
    }
}

using namespace zge;

LuaState::LuaState()
{
    m_luaState = luaL_newstate();
    if (!m_luaState) throw std::runtime_error("The Lua state could not be constructed.\n");
}

LuaState::~LuaState()
{
    lua_close(m_luaState);
    m_luaState = nullptr;
}

int LuaState::loadFile(std::string file)
{
    int error = luaL_loadfile(m_luaState, "variables.lua");

    if (error)
    {
        throw std::runtime_error(luaErrorAsString(m_luaState, error));
    }

    return error;
}

int LuaState::executeFile(std::string file)
{
    int error = lua_pcall(m_luaState, 0, 0, 0);

    if (error)
    {
        throw std::runtime_error(luaErrorAsString(m_luaState, error));
    }

    return error;
}

lua_State* LuaState::getRawState()
{
    return m_luaState;
}
