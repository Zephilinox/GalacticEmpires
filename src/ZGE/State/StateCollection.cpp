#include "ZGE/State/StateCollection.hpp"

//STD
#include <iostream>
#include <cassert>

namespace zge
{

StateCollection::StateCollection()
{
}

void StateCollection::pop()
{
    m_states.pop_back();
}

BaseState& StateCollection::getFromTop(unsigned offset)
{
    assert(m_states.size());
    return *m_states[m_states.size() - 1 - offset];
}

unsigned StateCollection::getSize()
{
    return m_states.size();
}

} //ZGE
