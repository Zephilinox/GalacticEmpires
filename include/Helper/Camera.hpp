#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera(sf::RenderWindow* window);
    void handleEvent(const sf::Event& e);
    void update(double dt);

    void resetZoom();

private:
    sf::RenderWindow* m_window;
    sf::View m_view;

    float m_zoomLimits[2];
    float m_zoomValue;

    float m_panBorderLimits[4];
    float m_panZonePercent;
    float m_panSpeed;

    float m_moveSpeed;

    bool m_updateWindow;
};

#endif //CAMERA_HPP
