#ifndef OPTIONSMENUSTATE_HPP
#define OPTIONSMENUSTATE_HPP

#include <SFML/Graphics.hpp>

#include "State/BaseState.hpp"
#include "GalacticEmpires.hpp"

class OptionsMenuState : public BaseState
{
public:
    OptionsMenuState(GalacticEmpires* galemp);
    bool handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    void onActive() override;
    void onInactive() override;

private:
    void exit();

    GalacticEmpires* m_galemp;
};

#endif //OPTIONSMENUSTATE_HPP
