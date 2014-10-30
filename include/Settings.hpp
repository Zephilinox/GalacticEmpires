#ifndef SETTINGS_HPP
#define SETTINGS_HPP

//STD
#include <unordered_map>
#include <string>

//3RD

//SELF

class Settings
{
public:
    Settings();
    void loadSettings();
    void saveSettings();

    bool getBoolSetting(std::string settingName);
    double getNumberSetting(std::string settingName);
    std::string getStringSetting(std::string settingName);

    void setBoolSetting(std::string settingName, bool val);
    void setNumberSetting(std::string settingName, double val);
    void setStringSetting(std::string settingName, std::string val);

private:
    std::unordered_map<std::string, bool> m_boolSettings;
    std::unordered_map<std::string, double> m_numberSettings;
    std::unordered_map<std::string, std::string> m_stringSettings;
};


#endif //SETTINGS_HPP
