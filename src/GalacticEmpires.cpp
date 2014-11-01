#include "GalacticEmpires.hpp"

#include <iostream>
#include <string>

#include <ZGE/Utility.hpp>
#include <ini_parser.hpp>

#include "State/TestState.hpp"
#include "State/SplashState.hpp"

GalacticEmpires::GalacticEmpires()
    : m_window(sf::VideoMode(1280, 720, 32), "Galactic Empires")
    , m_curState(nullptr)
    , m_prevFrameTime(sf::seconds(1.f/60.f))
{
    loadSettings();
    m_window.resetGLStates(); //This is required to show SFGUI if we don't draw with SFML at any point

    m_guiDesktop.LoadThemeFromFile("data/default.theme");
    m_stateMan.push<SplashState>(this);
}

void GalacticEmpires::run()
{
    gameLoop();
}

void GalacticEmpires::loadSettings()
{
    ini_parser iniParser("data/settings.ini");
    int width = iniParser.get_int("width", "Video");
    int height = iniParser.get_int("height", "Video");
    int bitDepth = iniParser.get_int("bitDepth", "Video");
    bool fullscreen = iniParser.get_bool("fullscreen", "Video");
    bool vsync = iniParser.get_bool("vsync", "Video");
    int maxFPS = iniParser.get_int("maxFPS", "Video");

    std::string version = "v";
    version += zge::toString(VERSION_MAJOR);
    version += ".";
    version += zge::toString(VERSION_MINOR);
    version += ".";
    version += zge::toString(VERSION_REVISION);

    m_window.create(sf::VideoMode(width, height, bitDepth), "Galactic Empires " + version, fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.setVerticalSyncEnabled(vsync);
    if (maxFPS) m_window.setFramerateLimit(maxFPS);
}

void GalacticEmpires::gameLoop()
{
    m_frameTime.restart();
    while (m_window.isOpen())
    {
        m_curState = m_stateMan.top();

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
    m_curState->handleEvent(e);

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
    m_curState->update(dt);
}

void GalacticEmpires::draw()
{
    m_window.clear(sf::Color(40, 40, 40));
    m_curState->draw(m_window);
    m_gui.Display(m_window);
    m_window.display();
}
