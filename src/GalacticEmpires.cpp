#include "GalacticEmpires.hpp"

//STD
#include <iostream>
#include <string>

GalacticEmpires::GalacticEmpires()
    : m_window(sf::VideoMode(1280, 720, 32), "Galactic Empires")
    , m_prevFrameTime(sf::seconds(1.f/60.f))
{
    luaL_openlibs(m_lua.getRawState());
}

void GalacticEmpires::run()
{
    if (m_lua.loadFile("settings.lua")) return;
    if (m_lua.executeFile("settings.lua")) return;

    m_settings.loadSettings(m_lua);
    std::cout << m_settings.getStringSetting("title") << "\n";
    m_settings.setStringSetting("title", "Lol");
    m_settings.saveSettings(m_lua);
    m_settings.loadSettings(m_lua);
    std::cout << m_settings.getStringSetting("title") << "\n";

    gameLoop();
}

void GalacticEmpires::gameLoop()
{
    m_frameTime.restart();
    while (m_window.isOpen())
    {
        while (m_window.pollEvent(m_event))
        {
            handleEvent(m_event);
        }

        update(m_prevFrameTime.asSeconds());
        draw();

        m_prevFrameTime = m_frameTime.getElapsedTime();
        m_frameTime.restart();
    }

}

void GalacticEmpires::handleEvent(const sf::Event& e)
{
    switch (e.type)
    {
        case sf::Event::Closed:
        {
            m_window.close();
            break;
        }

        default:
        {
            break;
        }
    }
}

void GalacticEmpires::update(float dt)
{

}

void GalacticEmpires::draw()
{
    m_window.clear(sf::Color(40, 40, 40));
    m_window.display();
}
