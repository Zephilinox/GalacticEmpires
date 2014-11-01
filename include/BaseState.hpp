#ifndef BASESTATE_HPP
#define BASESTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

class BaseState
{
public:
    virtual void handleEvent(const sf::Event& e) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual ~BaseState() = default;
};

#endif //BASESTATE_HPP
