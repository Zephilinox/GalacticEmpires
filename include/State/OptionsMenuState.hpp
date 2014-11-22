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
    bool applyChanges(const CEGUI::EventArgs& e);
    bool saveChanges(const CEGUI::EventArgs& e);

    GalacticEmpires* m_galemp;
    CEGUI::Window* m_rootWindow;
};

#endif //OPTIONSMENUSTATE_HPP
