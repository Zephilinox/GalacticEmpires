#include "State/MainMenuState.hpp"

#include "State/NewGameState.hpp"
#include "State/OptionsMenuState.hpp"

MainMenuState::MainMenuState(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window* root = wmgr.loadLayoutFromFile("MainMenu.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);
}

void MainMenuState::handleEvent(const sf::Event& e)
{
}

void MainMenuState::update(float dt)
{
    newGame();
}

void MainMenuState::draw(sf::RenderWindow& window) const
{

}

void MainMenuState::onActive()
{
}

void MainMenuState::onInactive()
{
}

void MainMenuState::newGame()
{
    m_galemp->getStateManager()->push<NewGameState>(m_galemp);
}

void MainMenuState::loadGame()
{

}

void MainMenuState::options()
{
    m_galemp->getStateManager()->push<OptionsMenuState>(m_galemp);
}

void MainMenuState::exit()
{
    m_galemp->getWindow()->close();
}
