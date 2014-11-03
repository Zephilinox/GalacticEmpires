#include "Helper/LuaState.hpp"

#include "Helper/Utility.hpp"

LuaState::LuaState()
{
    m_luaState = luaL_newstate();
    if (!m_luaState)
    {
        throw std::runtime_error("The LuaState could not be constructed\n");
    }

    luaL_openlibs(m_luaState);
}

LuaState::~LuaState()
{
    lua_close(m_luaState); //delete
    m_luaState = nullptr;
}

int LuaState::doFile(std::string file)
{
    int error = loadFile(file);
    if (error)
    {
        return error;
    }

    error = executeFile(file);
    return error;
}

int LuaState::loadFile(std::string file)
{
    lua_pushcfunction(m_luaState, traceback);
    int error = luaL_loadfile(m_luaState, file.c_str());

    #ifdef DEBUG
    if (error)
    {
        throw std::runtime_error("[LuaState::loadFile] " + luaErrorAsString(error) + "\n\n" + lua_tostring(m_luaState, -1));
    }
    #endif //DEBUG

    return error;
}

int LuaState::executeFile(std::string file)
{
    int error = lua_pcall(m_luaState, 0, 0, lua_gettop(m_luaState) - 1);

    #ifdef DEBUG
    if (error)
    {
        throw std::runtime_error("[LuaState::executeFile] " + luaErrorAsString(error) + "\n\n" + lua_tostring(m_luaState, -1));
    }

    #endif //DEBUG

    return error;
}

lua_State* LuaState::getRawState()
{
    return m_luaState;
}
