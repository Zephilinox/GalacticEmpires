#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

#include "GalacticEmpires.hpp"

class Camera
{
public:
    Camera(GalacticEmpires* galemp);
    void handleEvent(const sf::Event& e);
    void update(float dt);

    void resetZoom();

    const sf::View& getView() const {return m_view;}

private:
    void zoom(float zoomDelta);

    GalacticEmpires* m_galemp;
    sf::View m_view;

    float m_zoomLimits[2];
    float m_zoomValue;

    float m_panBorderLimits[4];
    float m_panZonePercent;
    float m_panSpeed;

    float m_moveSpeed;

    bool m_updateWindow;
    bool m_resetView;
};

#endif //CAMERA_HPP
