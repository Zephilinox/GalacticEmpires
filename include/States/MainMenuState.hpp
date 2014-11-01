#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP


//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/State/BaseState.hpp>
#include <ZGE/State/StateCollection.hpp>
#include <SFGUI/SFGUI.hpp>

//SELF

class MainMenuState : public zge::BaseState
{
public:
    MainMenuState(sf::RenderWindow& window, zge::StateCollection& stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

private:
    void exit();

    sfg::Window::Ptr m_guiMainMenu;

    bool m_exit;
};

#endif // MAINMENUSTATE_HPP
