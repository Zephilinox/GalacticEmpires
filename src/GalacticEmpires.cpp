#include "GalacticEmpires.hpp"

//STD
#include <iostream>
#include <string>

//3RD
//#include <ini_parser.hpp>
#include <ZGE/Utility.hpp>

//SELF
#include "States/SplashState.hpp"

GalacticEmpires::GalacticEmpires()
    : m_window(sf::VideoMode(1280, 720, 32), "Galactic Empires")
    , m_guiDesktop()
    , m_prevFrameTime(sf::seconds(1.f/60.f))
{
    loadSettings();
    m_stateHandler.getStateCollection().push<SplashState>(&m_window);
    m_guiDesktop.LoadThemeFromFile("data/default.theme");
}

void GalacticEmpires::run()
{
    gameLoop();
}

void GalacticEmpires::loadSettings()
{
    /*ini_parser iniParser("data/settings.ini");
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
    if (maxFPS) m_window.setFramerateLimit(maxFPS);*/
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
        postDraw();
    }
}

void GalacticEmpires::handleEvent(const sf::Event& e)
{
    m_stateHandler.handleEvent(m_event);

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
    m_stateHandler.update(dt);
}

void GalacticEmpires::draw()
{
    m_window.clear(sf::Color(40, 40, 40));
    m_stateHandler.draw(m_window);

    m_gui.Display(m_window);
    m_window.display();
}

void GalacticEmpires::postDraw()
{
    m_stateHandler.postDraw();
    m_prevFrameTime = m_frameTime.getElapsedTime();
    m_frameTime.restart();
}
