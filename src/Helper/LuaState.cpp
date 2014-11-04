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

int LuaState::loadFile(const std::string& file)
{
    lua_pushcfunction(m_luaState, traceback);
    int error = luaL_loadfile(m_luaState, file.c_str());

    if (error)
    {
        throw std::runtime_error("[LuaState::loadFile] " + luaErrorAsString(error) + "\n\n" + lua_tostring(m_luaState, -1));
    }

    return error;
}

int LuaState::execute()
{
    int error = lua_pcall(m_luaState, 0, 0, lua_gettop(m_luaState) - 1);

    if (error)
    {
        throw std::runtime_error("[LuaState::execute] " + luaErrorAsString(error) + "\n\n" + lua_tostring(m_luaState, -1));
    }

    return error;
}

luabridge::LuaRef LuaState::getGlobal(const std::string& varName)
{
    if (varName.find('.') == std::string::npos)
    {
        luabridge::LuaRef varRef = luabridge::getGlobal(m_luaState, varName.c_str());

        return varRef;
    }
    else
    {
        std::stringstream ss(varName);
        std::vector<std::string> vars;
        std::string splitVarName = "";

        while (std::getline(ss, splitVarName, '.'))
        {
            vars.push_back(splitVarName);
        }

        luabridge::LuaRef varRef = luabridge::getGlobal(m_luaState, "_G");

        if (vars.size())
        {
            for (unsigned i = 0; i < vars.size(); ++i)
            {
                varRef = luabridge::LuaRef(varRef[vars[i].c_str()]);
            }
        }
        else
        {
            varRef = luabridge::LuaRef(varRef[vars[0].c_str()]);
        }

        return varRef;
    }
}

lua_State* LuaState::getRawState()
{
    return m_luaState;
}
