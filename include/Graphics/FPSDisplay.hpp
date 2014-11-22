#ifndef FPSDISPLAY_HPP
#define FPSDISPLAY_HPP

#include <deque>

#include <SFML/Graphics.hpp>

#include "Graphics/TextHandler.hpp"

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
    std::deque<unsigned> m_FPSValues;

};

#endif //FPSDISPLAY_HPP
