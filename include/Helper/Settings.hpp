#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <unordered_map>

#include <ini_parser.hpp>

class Settings
{
    public:
        static void saveSettings();

        static void setValue(const std::string& name, int value, const std::string& section = "");
        static void setValue(const std::string& name, bool value, const std::string& section = "");
        static void setValue(const std::string& name, long value, const std::string& section = "");
        static void setValue(const std::string& name, float value, const std::string& section = "");
        static void setValue(const std::string& name, double value, const std::string& section = "");
        static void setValue(const std::string& name, const std::string& value, const std::string& section = "");

        static int getInt(const std::string& name, const std::string& section = "");
        static bool getBool(const std::string& name, const std::string& section = "");
        static long getLong(const std::string& name, const std::string& section = "");
        static float getFloat(const std::string& name, const std::string& section = "");
        static double getDouble(const std::string& name, const std::string& section = "");
        static std::string getString(const std::string& name, const std::string& section = "");

    private:
        static const std::string SETTINGS_FILE;
        static ini_parser m_parser;

        /* Maps a section name to the properties that have been changed in that section. */
        static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_sections;
};

#endif
