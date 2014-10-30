#include "Settings.hpp"

//STD
#include <iostream>

Settings::Settings()
{
}

void Settings::loadSettings()
{

}

void Settings::saveSettings()
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
    return "";
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

