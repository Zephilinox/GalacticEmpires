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

    bool m_updateWindow;
};

#endif //CAMERA_HPP
