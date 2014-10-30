#ifndef LUASTATE_HPP
#define LUASTATE_HPP

//STD
#include <string>
#include <vector>

//3RD
#include <lua.hpp>
#include <LuaBridge/Luabridge.h>

//SELF

namespace zge
{

class LuaState
{
public:
    LuaState();
    ~LuaState();

    template <typename T>
    T getGlobal(std::string varName);

    int loadFile(std::string file);
    int executeFile(std::string file);

    lua_State* getRawState();

private:
    lua_State* m_luaState;
};

template <typename T>
T LuaState::getGlobal(std::string varName)
{
    if (varName.find('.') == std::string::npos)
    {
        luabridge::LuaRef varRef = luabridge::getGlobal(m_luaState, varName.c_str());

        if (varRef.isNil())
        {
            throw std::runtime_error("'" + varName + "' is Nil");
        }

        return varRef.cast<T>();
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

        if (vars.size() > 1)
        {
            //We need to check the first value isn't nil as that is the root table which we later index from.
            luabridge::LuaRef varRef = luabridge::getGlobal(m_luaState, vars[0].c_str());

            if (varRef.isNil())
            {
                throw std::runtime_error("'" + vars[0] + "' is Nil, in request for '" + varName + "'");
            }

            for (unsigned i = 1; i < vars.size(); ++i)
            {
                varRef = luabridge::LuaRef(varRef[vars[i].c_str()]);

                if (varRef.isNil())
                {
                    throw std::runtime_error("'" + vars[i] + "' is Nil, in request for '" + varName + "'");
                }
            }

            return varRef.cast<T>();
        }
        else
        {
            throw std::runtime_error("'" + varName + "' is invalid");
        }
    }
}

} //ZGE

#endif //LUASTATE_HPP
