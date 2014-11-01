#include "States/MainMenuState.hpp"

//STD

//3RD

//SELF

MainMenuState::MainMenuState(sf::RenderWindow& window, zge::StateCollection& stateCollection)
    : BaseState(window, stateCollection)
    , m_guiMainMenu(sfg::Window::Create(sfg::Window::BACKGROUND))
{
    m_stateID = "MainMenuState";
    m_guiMainMenu->SetAllocation(sf::FloatRect(1280/3, 720/8, 1280/3, 720 - 720/4));
}

void MainMenuState::handleEvent(const sf::Event& event)
{
    m_guiMainMenu->HandleEvent(event);
}

void MainMenuState::update(float dt)
{
    m_guiMainMenu->Update(dt);
}

void MainMenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void MainMenuState::postDraw()
{
}
