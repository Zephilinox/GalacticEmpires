#include "Helper/Camera.hpp"

#include <iostream>

Camera::Camera(sf::RenderWindow* window)
    : m_window(window)
    , m_view(m_window->getView())
    , m_panZonePercent(0.1f)
    , m_panSpeed(4.f)
    , m_updateWindow(false)
{
    m_panBorderLimits[0] = m_window->getSize().x * m_panZonePercent;
    m_panBorderLimits[1] = m_window->getSize().x * (1.f-m_panZonePercent);
    m_panBorderLimits[2] = m_window->getSize().y * m_panZonePercent;
    m_panBorderLimits[3] = m_window->getSize().y * (1.f-m_panZonePercent);
}

void Camera::handleEvent(const sf::Event& e)
{
    switch (e.type)
    {
        case sf::Event::MouseWheelMoved:
        {
            m_view.zoom(1.f + (e.mouseWheel.delta * -0.1)); //TODO: Make Smooth Zoom
            m_updateWindow = true;
        }

        case sf::Event::Resized:
        {
            m_panBorderLimits[0] = m_window->getSize().x * m_panZonePercent;
            m_panBorderLimits[1] = m_window->getSize().x * (1.f-m_panZonePercent);
            m_panBorderLimits[2] = m_window->getSize().y * m_panZonePercent;
            m_panBorderLimits[3] = m_window->getSize().y * (1.f-m_panZonePercent);
        }

        default:
        {
            break;
        }
    }
}

void Camera::update(double dt)
{
    sf::Vector2u mousePos(sf::Mouse::getPosition(*m_window));

    if (mousePos.x <= m_panBorderLimits[0]) //unsigned, so don't need to check below 0;
    {
        float deltaX = mousePos.x - m_panBorderLimits[0];
        m_view.move(m_panSpeed * deltaX * dt, 0);
        m_updateWindow = true;
    }
    else if (mousePos.x <= m_window->getSize().x && mousePos.x >= m_panBorderLimits[1])
    {
        float deltaX = mousePos.x - m_panBorderLimits[1];
        m_view.move(m_panSpeed * deltaX * dt, 0);
        m_updateWindow = true;
    }

    if (mousePos.y <= m_panBorderLimits[2])
    {
        float deltaY = mousePos.y - m_panBorderLimits[2];
        m_view.move(0, m_panSpeed * deltaY * dt);
        m_updateWindow = true;
    }
    else if (mousePos.y <= m_window->getSize().x && mousePos.y >= m_panBorderLimits[3])
    {
        float deltaY = mousePos.y - m_panBorderLimits[3];
        m_view.move(0, m_panSpeed * deltaY * dt);
        m_updateWindow = true;
    }

    if (m_updateWindow)
    {
        m_window->setView(m_view);
    }
}

void Camera::resetZoom()
{

}
