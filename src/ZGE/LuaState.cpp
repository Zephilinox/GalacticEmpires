#include "ZGE/LuaState.hpp"

//STD
#include <iostream>

//3RD
#include <ZGE/Utility.hpp>

//SELF

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
    int error = luaL_loadfile(m_luaState, file.c_str());

    if (error)
    {
        throw std::runtime_error(luaErrorAsString(m_luaState, error) + " [" + file + "]");
    }

    return error;
}

int LuaState::executeFile(std::string file)
{
    int error = lua_pcall(m_luaState, 0, 0, 0);

    if (error)
    {
        throw std::runtime_error(luaErrorAsString(m_luaState, error) + " [" + file + "]");
    }

    return error;
}

lua_State* LuaState::getRawState()
{
    return m_luaState;
}
