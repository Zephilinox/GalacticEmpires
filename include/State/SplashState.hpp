#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

#include <SFML/Graphics.hpp>

#include "State/BaseState.hpp"
#include "GalacticEmpires.hpp"

class SplashState : public BaseState
{
public:
    SplashState(GalacticEmpires* galemp);
    bool handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    void onActive() override;
    void onInactive() override;

private:
    GalacticEmpires* m_galemp;

    sf::Clock m_clock;
};

#endif //SPLASHSTATE_HPP
