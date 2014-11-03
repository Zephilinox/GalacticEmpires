#include "Helper/Camera.hpp"

#include <iostream>

Camera::Camera(sf::RenderWindow* window)
    : m_window(window)
    , m_view(m_window->getView())
    , m_updateWindow(false)
{

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

        default:
        {
            break;
        }
    }
}

void Camera::update(double dt)
{
    sf::Vector2i mousePos(sf::Mouse::getPosition(*m_window));
    float panBorderLimits[4];
    panBorderLimits[0] = m_window->getSize().x * 0.10;
    panBorderLimits[1] = m_window->getSize().x * 0.90;
    panBorderLimits[2] = m_window->getSize().y * 0.10;
    panBorderLimits[3] = m_window->getSize().y * 0.90;

    if (mousePos.x >= 0 && mousePos.x <= panBorderLimits[0])
    {
        float deltaX = panBorderLimits[0] - mousePos.x;
        m_view.move(-8 * deltaX * dt, 0);
        m_updateWindow = true;
    }
    else if (mousePos.x <= m_window->getSize().x && mousePos.x >= panBorderLimits[1])
    {
        float deltaX = panBorderLimits[1] - mousePos.x;
        m_view.move(-8 * deltaX * dt, 0);
        m_updateWindow = true;
    }

    if (mousePos.y >= 0 && mousePos.y <= panBorderLimits[2])
    {
        float deltaY = panBorderLimits[2] - mousePos.y;
        m_view.move(0, -8 * deltaY * dt);
        m_updateWindow = true;
    }
    else if (mousePos.y <= m_window->getSize().x && mousePos.y >= panBorderLimits[3])
    {
        float deltaY = panBorderLimits[3] - mousePos.y;
        m_view.move(0, -8 * deltaY * dt);
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
