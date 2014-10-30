#ifndef BASESTATE_HPP
#define BASESTATE_HPP

//STD
#include <string>

//3RD
#include <SFML/Graphics.hpp>

//SELF
namespace zge
{

class StateCollection;

class BaseState : public sf::Drawable
{
public:
    BaseState(sf::RenderWindow& window, StateCollection& stateCollection);
    virtual ~BaseState();

    bool operator==(BaseState& state);

    virtual void handleEvent(const sf::Event& event);
    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void postDraw();

    std::string getStateID();
    bool transparent;

protected:
    sf::RenderWindow& m_window;
    StateCollection& m_stateCollection;

    std::string m_stateID;
};

} //ZGE


#endif //BASESTATE_HPP
