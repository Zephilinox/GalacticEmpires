#include "Helper/LuaState.hpp"

#include "Helper/Utility.hpp"

LuaState::LuaState()
{
    m_luaState = luaL_newstate();
    if (!m_luaState)
    {
        throw std::runtime_error("The LuaState could not be constructed\n");
    }

    luaL_openlibs(m_luaState); //add the default lua libraries
}

LuaState::~LuaState()
{
    lua_close(m_luaState); //delete
    m_luaState = nullptr;
}

int LuaState::loadFile(const std::string& file)
{
    lua_pushcfunction(m_luaState, traceback); //give lua knowledge of our stacktrace function. POSSIBLE BUG: loading multiple files will add too many of these c functions?
    int error = luaL_loadfile(m_luaState, file.c_str());

    if (error)
    {
        throw std::runtime_error("[LuaState::loadFile] " + luaErrorAsString(error) + "\n\n" + lua_tostring(m_luaState, -1));
    }

    return error;
}

int LuaState::execute()
{
    int error = lua_pcall(m_luaState, 0, 0, lua_gettop(m_luaState) - 1); //protected call to the entire lua state (execute 'main'), using the stack trace function we pushed to the top of the lua stack

    if (error)
    {
        throw std::runtime_error("[LuaState::execute] " + luaErrorAsString(error) + "\n\n" + lua_tostring(m_luaState, -1));
    }

    return error;
}

luabridge::LuaRef LuaState::getGlobal(const std::string& varName)
{
    if (varName.find('.') == std::string::npos) //If there is no '.', just return it
    {
        luabridge::LuaRef varRef = luabridge::getGlobal(m_luaState, varName.c_str());

        return varRef;
    }
    else
    {
        std::stringstream ss(varName);
        std::vector<std::string> vars;
        std::string splitVarName = "";

        //Explode the string in to various strings, using '.' as a delimiter
        while (std::getline(ss, splitVarName, '.'))
        {
            vars.push_back(splitVarName);
        }

        luabridge::LuaRef varRef = luabridge::getGlobal(m_luaState, "_G");

        //Iterate through tables of tables until we get to the end
        for (unsigned i = 0; i < vars.size(); ++i)
        {
            varRef = luabridge::LuaRef(varRef[vars[i].c_str()]);
        }

        return varRef;
    }
}

lua_State* LuaState::getRawState()
{
    return m_luaState;
}

int LuaState::traceback(lua_State* L)
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