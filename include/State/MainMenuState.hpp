#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>

#include "State/BaseState.hpp"
#include "GalacticEmpires.hpp"

class MainMenuState : public BaseState
{
public:
    MainMenuState(GalacticEmpires* galemp);
    void handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    void onActive() override;
    void onInactive() override;

private:
    void newGame();
    void loadGame();
    void options();
    void exit();

    GalacticEmpires* m_galemp;
    CEGUI::Window* m_rootWindow;
};

#endif //MAINMENUSTATE_HPP
