#ifndef BASESTATE_HPP
#define BASESTATE_HPP

#include <SFML/Graphics.hpp>

class BaseState
{
public:
    virtual ~BaseState() = default;

    virtual bool handleEvent(const sf::Event& e) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void onActive() = 0;
    virtual void onInactive() = 0;
};

#endif //BASESTATE_HPP
