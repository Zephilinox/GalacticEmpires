#ifndef TESTSTATE_HPP
#define TESTSTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "BaseState.hpp"

class TestState: public BaseState
{
public:
    TestState();
    void handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

private:
    sf::RectangleShape rs;
};

#endif //TESTSTATE_HPP
