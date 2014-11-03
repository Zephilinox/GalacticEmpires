#ifndef OPTIONSMENUSTATE_HPP
#define OPTIONSMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "State/BaseState.hpp"
#include "GalacticEmpires.hpp"

class OptionsMenuState : public BaseState
{
public:
    OptionsMenuState(GalacticEmpires* galemp);
    void handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    void onActive() override;
    void onInactive() override;

private:
    void exit();

    GalacticEmpires* m_galemp;

    sfg::Window::Ptr m_guiWindow;
};

#endif //OPTIONSMENUSTATE_HPP
