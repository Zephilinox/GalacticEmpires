#ifndef STATEHANDLER_HPP
#define STATEHANDLER_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "ZGE/State/BaseState.hpp"
#include "ZGE/State/StateCollection.hpp"

namespace zge
{

class StateHandler
{
public:
    StateHandler();
    void handleEvent(const sf::Event event);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void postDraw();

    StateCollection& getStateCollection();

private:
    StateCollection m_stateCollection;
};

} //ZGE


#endif //STATEHANDLER_HPP
