#include "StateManager.hpp"

StateManager::StateManager()
{
}

std::shared_ptr<BaseState> StateManager::top()
{
    if (m_states.size())
    {
        return m_states.top();
    }

    return std::shared_ptr<BaseState>(nullptr);
}

void StateManager::pop()
{
    if (m_states.size())
    {
        m_states.pop();
    }
}
