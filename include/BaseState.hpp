#ifndef BASESTATE_HPP
#define BASESTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

class BaseState
{
public:
    BaseState();
    virtual void handleEvent(const sf::Event& e);
    virtual void update(float dt);
    virtual void draw(sf::RenderWindow& window) const;

    virtual ~BaseState() = default;

private:
};

#endif //BASESTATE_HPP
