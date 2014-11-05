#include "Helper/Settings.hpp"

const std::string Settings::SETTINGS_FILE = "data/settings.ini";
ini_parser Settings::m_parser(SETTINGS_FILE);
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> Settings::m_sections;

void Settings::setValue(const std::string& name, int value, const std::string& section)
{

}

void Settings::setValue(const std::string& name, bool value, const std::string& section)
{

}

void Settings::setValue(const std::string& name, long value, const std::string& section)
{

}

void Settings::setValue(const std::string& name, float value, const std::string& section)
{

}

void Settings::setValue(const std::string& name, double value, const std::string& section)
{

}

void Settings::setValue(const std::string& name, const std::string& value, const std::string& section)
{

}

int Settings::getInt(const std::string& name, const std::string& section)
{
    return 0;
}

bool Settings::getBool(const std::string& name, const std::string& section)
{
    return true;
}

long Settings::getLong(const std::string& name, const std::string& section)
{
    return 0L;
}

float Settings::getFloat(const std::string& name, const std::string& section)
{
    return 0.f;
}

double Settings::getDouble(const std::string& name, const std::string& section)
{
    return 0.0;
}

std::string Settings::getString(const std::string& name, const std::string& section)
{
    return "";
}
