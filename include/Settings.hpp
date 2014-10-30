#ifndef SETTINGS_HPP
#define SETTINGS_HPP

//STD
#include <unordered_map>
#include <string>

//3RD
#include <ZGE/LuaState.hpp>

//SELF

class Settings
{
public:
    Settings();
    void loadSettings(zge::LuaState& state);
    void saveSettings(zge::LuaState& state);

    bool getBoolSetting(std::string settingName);
    int getIntSetting(std::string settingName);
    double getDoubleSetting(std::string settingName);
    std::string getStringSetting(std::string settingName);

    void setBoolSetting(std::string settingName, bool val);
    void setIntSetting(std::string settingName, int val);
    void setDoubleSetting(std::string settingName, double val);
    void setStringSetting(std::string settingName, std::string val);

private:
    std::unordered_map<std::string, bool> m_boolSettings;
    std::unordered_map<std::string, int> m_intSettings;
    std::unordered_map<std::string, double> m_doubleSettings;
    std::unordered_map<std::string, std::string> m_stringSettings;
};


#endif //SETTINGS_HPP
