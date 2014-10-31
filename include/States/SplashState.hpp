#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/State/BaseState.hpp>
#include <SFGUI/SFGUI.hpp>

//SELF

class SplashState : public zge::BaseState
{
public:
    SplashState(sf::RenderWindow& window, zge::StateCollection& stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

private:
    sfg::Window::Ptr m_guiWindow;
    sfg::Spinner::Ptr m_guiSpinner;
};

#endif // SPLASHSTATE_HPP
