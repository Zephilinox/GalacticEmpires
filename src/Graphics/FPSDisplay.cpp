#include "Graphics/FPSDisplay.hpp"

#include <cmath>

#include "Helper/Utility.hpp"

FPSDisplay::FPSDisplay()
    : m_fpsText("", "data/cegui/fonts/DejaVuSans.ttf", 36, sf::Vector2f(0, 0), TextHandler::Origin::TopLeft)
    , m_visible(true)
{
    m_fpsText.setBorderColor(sf::Color::Black);
    m_fpsText.setBorderEnabled(true);
}

bool FPSDisplay::handleEvent(const sf::Event& e)
{
    switch (e.type)
    {
        case sf::Event::KeyPressed:
        {
            if (e.key.code == sf::Keyboard::F8)
            {
                m_visible = !m_visible;
            }
            break;
        }

        default:
        {
            break;
        }
    }

    return false;
}

void FPSDisplay::update(float dt)
{
    static const unsigned updatesPerSecond = 10;

    if (m_updateClock.getElapsedTime() > sf::seconds(1.f / updatesPerSecond))
    {
        //Calculate average FPS based on values from the last second
        m_FPSValues.push_back(unsigned(std::floor(1.f / dt)));
        if (m_FPSValues.size() > updatesPerSecond)
        {
            m_FPSValues.pop_front();
        }

        unsigned avgFPS = 0;
        for (unsigned fps : m_FPSValues)
        {
            avgFPS += fps;
        }
        avgFPS = unsigned(std::floor(avgFPS/m_FPSValues.size()));

        //Update the FPS
        m_fpsText.setText(toString(avgFPS));
        m_fpsText.update();
        m_updateClock.restart();
    }
}

void FPSDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_visible)
    {
        //We have to reset the view in order to render the text relative to the window, rather than the world position.
        sf::View oldView = target.getView();
        target.setView(target.getDefaultView());

        target.draw(m_fpsText, states);

        target.setView(oldView);
    }
}
