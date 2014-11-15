#include "State/MainMenuState.hpp"

#include "State/NewGameState.hpp"
#include "State/OptionsMenuState.hpp"

MainMenuState::MainMenuState(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    m_rootWindow = wmgr.loadLayoutFromFile("MainMenu.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_rootWindow);
}

bool MainMenuState::handleEvent(const sf::Event& e)
{
    return false;
}

void MainMenuState::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        newGame();
    }
}

void MainMenuState::draw(sf::RenderWindow& window) const
{

}

void MainMenuState::onActive()
{
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_rootWindow);
    auto* window = m_rootWindow->getChild("testWindow");
    window->setVisible(true);
}

void MainMenuState::onInactive()
{
    auto* window = m_rootWindow->getChild("testWindow");
    window->setVisible(false);
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
