#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

//STD

//3RD

//SELF
#include "BaseState.hpp"

class GalacticEmpires;

class StateManager
{
public:
    StateManager();

    template <class T> void push(GalacticEmpires* galpires);

    BaseState* m_state;
private:
};

template <class T>
void StateManager::push(GalacticEmpires* galpires)
{
    m_state = new T(galpires);
}

#endif //STATEMANAGER_HPP
