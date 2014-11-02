#include "GalacticEmpires.hpp"

#include <iostream>
#include <string>

#include <Helper/Utility.hpp>
#include <ini_parser.hpp>

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

sf::RenderWindow* GalacticEmpires::getWindow()
{
    return &m_window;
}

StateManager<GalacticEmpires>* GalacticEmpires::getStateManager()
{
    return &m_stateMan;
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
    version += toString(VERSION_MAJOR);
    version += ".";
    version += toString(VERSION_MINOR);
    version += ".";
    version += toString(VERSION_REVISION);

    sf::VideoMode vm(width, height, bitDepth);

    if (!vm.isValid())
    {
        if (fullscreen)
        {
            throw std::runtime_error("Invalid Video Settings for Fullscreen (Width, Height, or BitDepth)");
        }
        else if (width == 0 || height == 0)
        {
            vm = sf::VideoMode::getDesktopMode();
            iniParser.set_value("width", int(vm.width), "Video");
            iniParser.set_value("height", int(vm.height), "Video");
            iniParser.set_value("bitDepth", int(vm.bitsPerPixel), "Video");
            fullscreen = true;
            iniParser.set_value("fullscreen", fullscreen, "Video");
        }
    }

    m_window.create(vm, "Galactic Empires " + version, fullscreen ? sf::Style::Fullscreen : sf::Style::Default);

    m_window.setVerticalSyncEnabled(vsync);

    if (maxFPS)
    {
        m_window.setFramerateLimit(maxFPS);
    }
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

        case sf::Event::KeyPressed:
        {
            if (e.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
            }
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
