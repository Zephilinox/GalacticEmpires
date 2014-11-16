#ifndef FPSDISPLAY_HPP
#define FPSDISPLAY_HPP

#include <SFML/Graphics.hpp>

#include "TextHandler.hpp"

class FPSDisplay : public sf::Drawable
{
public:
    FPSDisplay();
    bool handleEvent(const sf::Event& e);
    void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    TextHandler m_fpsText;
    bool m_visible;
    sf::Clock m_updateClock;
};

#endif //FPSDISPLAY_HPP
