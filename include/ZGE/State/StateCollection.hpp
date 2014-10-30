#ifndef STATECOLLECTION_HPP
#define STATECOLLECTION_HPP

//STD
#include <vector>
#include <memory>

//3RD
#include <SFML/Graphics.hpp>

//SELF
namespace zge
{

class BaseState;

class StateCollection
{
public:
    StateCollection();

    template <class T>
    void push(sf::RenderWindow& window);

    void pop();

    BaseState& getFromTop(unsigned offset);

    unsigned getSize();

private:
    std::vector<std::shared_ptr<BaseState>> m_states;
};

//Template functions
template <class T>
void StateCollection::push(sf::RenderWindow& window)
{
    m_states.push_back(std::make_shared<T>(T(window, *this)));
}

} //ZGE

#endif //STATECOLLECTION_HPP
