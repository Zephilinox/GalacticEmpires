#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <unordered_map>

#include <ini_parser.hpp>

class Settings
{
    public:
        Settings(const std::string& filename);

        void save();

        void setValue(const std::string& name, int value, const std::string& section = "");
        void setValue(const std::string& name, bool value, const std::string& section = "");
        void setValue(const std::string& name, long value, const std::string& section = "");
        void setValue(const std::string& name, float value, const std::string& section = "");
        void setValue(const std::string& name, double value, const std::string& section = "");
        void setValue(const std::string& name, const std::string& value, const std::string& section = "");

        int getInt(const std::string& name, const std::string& section = "");
        bool getBool(const std::string& name, const std::string& section = "");
        long getLong(const std::string& name, const std::string& section = "");
        float getFloat(const std::string& name, const std::string& section = "");
        double getDouble(const std::string& name, const std::string& section = "");
        std::string getString(const std::string& name, const std::string& section = "");

    private:
        ini_parser m_parser;

        /* Maps a section name to the properties that have been changed in that section. */
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_sections;
};

#endif
