#include "Settings.hpp"

//STD
#include <iostream>

Settings::Settings()
{
}

void Settings::loadSettings(zge::LuaState& state)
{
    luabridge::LuaRef tbl = luabridge::getGlobal(state.getRawState(), "_G")["settings"];

    for (luabridge::Iterator it(tbl); !it.isNil(); ++it)
    {
        std::string key = it.key().cast<std::string>(); //removes quotes

        if (it.value().isBoolean())
        {
            m_boolSettings[key] = it.value().cast<bool>();
        }
        else if (it.value().isNumber())
        {
            m_numberSettings[key] = it.value().cast<double>();
        }
        else if (it.value().isString())
        {
            m_stringSettings[key] = it.value().cast<std::string>();
        }
    }
}

void Settings::saveSettings(zge::LuaState& state)
{

}

bool Settings::getBoolSetting(std::string settingName)
{
    return false;
}

double Settings::getNumberSetting(std::string settingName)
{
    return 0.0;
}

std::string Settings::getStringSetting(std::string settingName)
{
    return m_stringSettings[settingName];
}


void Settings::setBoolSetting(std::string settingName, bool val)
{

}

void Settings::setNumberSetting(std::string settingName, double val)
{

}

void Settings::setStringSetting(std::string settingName, std::string val)
{
    m_stringSettings[settingName] = val;
}

