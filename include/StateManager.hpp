#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

//STD
#include <memory>
#include <stack>

//3RD

//SELF
#include "BaseState.hpp"

//IDEA: Make class template and use it to determine the pointer to the class

class GalacticEmpires;

class StateManager
{
public:
    StateManager();

    std::shared_ptr<BaseState> top();
    template <class T> void push(GalacticEmpires* galpires);
    void pop();

private:
    std::stack<std::shared_ptr<BaseState>> m_states;
};

template <class T>
void StateManager::push(GalacticEmpires* galpires)
{
    m_states.push(std::make_shared<T>(galpires));
}

#endif //STATEMANAGER_HPP
