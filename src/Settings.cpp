#include "Settings.hpp"

//STD
#include <iostream>

Settings::Settings()
{
}

void Settings::loadSettings(zge::LuaState& state)
{

}

void Settings::saveSettings(zge::LuaState& state)
{

}

bool Settings::getBoolSetting(std::string settingName)
{
    return false;
}

int Settings::getIntSetting(std::string settingName)
{
    return 0;
}

double Settings::getDoubleSetting(std::string settingName)
{
    return 0.0;
}

std::string Settings::getStringSetting(std::string settingName)
{
    return "fail";
}


void Settings::setBoolSetting(std::string settingName, bool val)
{

}

void Settings::setIntSetting(std::string settingName, int val)
{

}

void Settings::setDoubleSetting(std::string settingName, double val)
{

}

void Settings::setStringSetting(std::string settingName, std::string val)
{

}

