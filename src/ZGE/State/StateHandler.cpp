#include "ZGE/State/StateHandler.hpp"

namespace zge
{

StateHandler::StateHandler()
{
}

void StateHandler::handleEvent(const sf::Event event)
{
    if (m_stateCollection.getSize()) m_stateCollection.getFromTop(0).handleEvent(event);
}

void StateHandler::update(float dt)
{
    if (m_stateCollection.getSize()) m_stateCollection.getFromTop(0).update(dt);
}

void StateHandler::draw(sf::RenderWindow& window)
{
    if (m_stateCollection.getSize() > 1 && m_stateCollection.getFromTop(0).transparent) window.draw(m_stateCollection.getFromTop(1));

    if (m_stateCollection.getSize()) window.draw(m_stateCollection.getFromTop(0));
}

void StateHandler::postDraw()
{

    if (m_stateCollection.getSize()) m_stateCollection.getFromTop(0).postDraw();
}

StateCollection& StateHandler::getStateCollection()
{
    return m_stateCollection;
}

} //ZGE

