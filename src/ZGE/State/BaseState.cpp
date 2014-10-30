#include "ZGE/State/BaseState.hpp"

//STD
#include <iostream>

namespace zge
{

BaseState::BaseState(sf::RenderWindow& window, StateCollection& stateCollection):
transparent(false),
m_window(window),
m_stateCollection(stateCollection),
m_stateID("BaseState")
{
    //std::cout << "[BaseState] Constructor\n";
}

BaseState::~BaseState()
{
    //std::cout << "[BaseState] Destructor\n";
}

bool BaseState::operator==(BaseState& state)
{
    return m_stateID == state.getStateID();
}

void BaseState::handleEvent(const sf::Event& event)
{
    //std::cout << "[BaseState] handleEvent\n";
}

void BaseState::update(float dt)
{
    //std::cout << "[BaseState] update\n";
}

void BaseState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //std::cout << "[BaseState] draw\n";
}

void BaseState::postDraw()
{
    //std::cout << "[BaseState] postDraw\n";
}

std::string BaseState::getStateID()
{
    return m_stateID;
}

} //ZGE
