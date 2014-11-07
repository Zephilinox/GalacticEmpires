#include "Helper/Camera.hpp"

#include <iostream>

#include <Thor/Input.hpp>

Camera::Camera(GalacticEmpires* galemp)
    : m_galemp(galemp)
    , m_view(m_galemp->getWindow()->getView())
    , m_zoomValue(1.f)
    , m_panZonePercent(0.1f)
    , m_panSpeed(4.f)
    , m_moveSpeed(512.f)
    , m_updateWindow(false)
{
    m_view.setCenter(0, 0);
    m_updateWindow = true; //assigned here for clarity

    m_zoomLimits[0] = 0.49f;
    m_zoomLimits[1] = 5.01f;

    m_panBorderLimits[0] = m_galemp->getWindow()->getSize().x * m_panZonePercent;
    m_panBorderLimits[1] = m_galemp->getWindow()->getSize().x * (1.f-m_panZonePercent);
    m_panBorderLimits[2] = m_galemp->getWindow()->getSize().y * m_panZonePercent;
    m_panBorderLimits[3] = m_galemp->getWindow()->getSize().y * (1.f-m_panZonePercent);
}

void Camera::handleEvent(const sf::Event& e)
{
    switch (e.type)
    {
        case sf::Event::MouseWheelMoved:
        {
            zoom(e.mouseWheel.delta * -0.1f);

            break;
        }

        case sf::Event::Resized:
        {
            m_view.setSize(m_galemp->getWindow()->getSize().x * m_zoomValue, m_galemp->getWindow()->getSize().y * m_zoomValue);
            m_panBorderLimits[0] = m_galemp->getWindow()->getSize().x * m_panZonePercent;
            m_panBorderLimits[1] = m_galemp->getWindow()->getSize().x * (1.f-m_panZonePercent);
            m_panBorderLimits[2] = m_galemp->getWindow()->getSize().y * m_panZonePercent;
            m_panBorderLimits[3] = m_galemp->getWindow()->getSize().y * (1.f-m_panZonePercent);
            m_updateWindow = true;
            break;
        }

        case sf::Event::KeyPressed:
        {
            if (e.key.code == thor::toKeyboardKey(m_galemp->getSettings()->getString("zoomIn", "Controls")))
            {
                zoom(-0.1f);
            }

            if (e.key.code == thor::toKeyboardKey(m_galemp->getSettings()->getString("zoomOut", "Controls")))
            {
                zoom(0.1f);
            }
            break;
        }

        default:
        {
            break;
        }
    }
}

void Camera::update(double dt)
{
    sf::Vector2u mousePos(sf::Mouse::getPosition(*m_galemp->getWindow()));

    if (mousePos.x <= m_panBorderLimits[0]) //unsigned, so don't need to check below 0;
    {
        float deltaX = mousePos.x - m_panBorderLimits[0];
        m_view.move(m_panSpeed * deltaX * dt, 0);
        m_updateWindow = true;
    }
    else if (mousePos.x <= m_galemp->getWindow()->getSize().x && mousePos.x >= m_panBorderLimits[1])
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
    else if (mousePos.y <= m_galemp->getWindow()->getSize().x && mousePos.y >= m_panBorderLimits[3])
    {
        float deltaY = mousePos.y - m_panBorderLimits[3];
        m_view.move(0, m_panSpeed * deltaY * dt);
        m_updateWindow = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        m_view.move(-m_moveSpeed * dt, 0);
        m_updateWindow = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        m_view.move(m_moveSpeed * dt, 0);
        m_updateWindow = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        m_view.move(0, -m_moveSpeed * dt);
        m_updateWindow = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        m_view.move(0, m_moveSpeed * dt);
        m_updateWindow = true;
    }

    if (m_updateWindow)
    {
        m_galemp->getWindow()->setView(m_view);
    }
}

void Camera::resetZoom()
{

}

void Camera::zoom(float zoomDelta)
{
    if (m_zoomValue + zoomDelta >= m_zoomLimits[0] &&
        m_zoomValue + zoomDelta <= m_zoomLimits[1])
    {
        m_zoomValue += zoomDelta;
        //m_view.zoom(1.f + zoomDelta); //TODO: Make Smooth Zoom
        m_view.setSize(sf::Vector2f(m_galemp->getWindow()->getSize()) * m_zoomValue);
        m_updateWindow = true;
    }

    std::cout << "Camera [" << m_view.getSize().x << ", " << m_view.getSize().y << "] = " << m_zoomValue * 100 << "%\n";
}

