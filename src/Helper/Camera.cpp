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
    if (m_updateWindow)
    {
        m_window->setView(m_view);
    }
}

void Camera::resetZoom()
{

}
