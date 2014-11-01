#ifndef TESTSTATE_HPP
#define TESTSTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

//SELF
#include "BaseState.hpp"
#include "GalacticEmpires.hpp"

class TestState: public BaseState
{
public:
    TestState(GalacticEmpires* galpires);
    void handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

private:
    void doShit();

    GalacticEmpires* m_galpires;
    sf::RectangleShape rs;
    bool m_hasShat;

    sfg::Window::Ptr m_guiWindow;
    sfg::Button::Ptr m_guiBtn;
};

#endif //TESTSTATE_HPP
