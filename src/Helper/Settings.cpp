#include "Helper/Utility.hpp"
#include "Helper/Settings.hpp"

const std::string Settings::SETTINGS_FILE = "data/settings.ini";
ini_parser Settings::m_parser(SETTINGS_FILE);
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> Settings::m_sections;

void Settings::save()
{
    for (const auto& section : m_sections)
    {
        for (const auto& property : section.second)
        {
            m_parser.set_value(property.first, property.second, section.first);
        }
    }

    m_sections.clear();
}

void Settings::setValue(const std::string& name, int value, const std::string& section)
{
    m_sections[section][name] = toString(value);
}

void Settings::setValue(const std::string& name, bool value, const std::string& section)
{
    m_sections[section][name] = (value ? m_parser.BOOL_TRUE : m_parser.BOOL_FALSE);
}

void Settings::setValue(const std::string& name, long value, const std::string& section)
{
    m_sections[section][name] = toString(value);
}

void Settings::setValue(const std::string& name, float value, const std::string& section)
{
    m_sections[section][name] = toString(value);
}

void Settings::setValue(const std::string& name, double value, const std::string& section)
{
    m_sections[section][name] = toString(value);
}

void Settings::setValue(const std::string& name, const std::string& value, const std::string& section)
{
    m_sections[section][name] = toString(value);
}

int Settings::getInt(const std::string& name, const std::string& section)
{
    return m_parser.get_int(name, section);
}

bool Settings::getBool(const std::string& name, const std::string& section)
{
    return m_parser.get_bool(name, section);
}

long Settings::getLong(const std::string& name, const std::string& section)
{
    return m_parser.get_long(name, section);
}

float Settings::getFloat(const std::string& name, const std::string& section)
{
    return m_parser.get_float(name, section);
}

double Settings::getDouble(const std::string& name, const std::string& section)
{
    return m_parser.get_double(name, section);
}

std::string Settings::getString(const std::string& name, const std::string& section)
{
    return m_parser.get_string(name, section);
}
