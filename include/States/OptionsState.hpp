#ifndef OPTIONSSTATE_HPP
#define OPTIONSSTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/State/BaseState.hpp>
#include <ZGE/State/StateCollection.hpp>
#include <SFGUI/SFGUI.hpp>

//SELF

class OptionsState : public zge::BaseState
{
public:
    OptionsState(sf::RenderWindow& window, zge::StateCollection& stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

private:
    sfg::Window::Ptr m_guiWindow;
};

#endif //OPTIONSSTATE_HPP
