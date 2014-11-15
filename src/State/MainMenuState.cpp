#include "State/MainMenuState.hpp"

#include "State/NewGameState.hpp"
#include "State/OptionsMenuState.hpp"

MainMenuState::MainMenuState(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
    //Get the window manager, load the layout from the file, and then set the root window in order to use that and all of its children
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    m_rootWindow = wmgr.loadLayoutFromFile("MainMenu.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_rootWindow);

    //Set up callback functions for button clicks
    auto* newGameButton = m_rootWindow->getChild("MainMenu/NewGame");
    newGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuState::newGame, this));

    auto* optionsButton = m_rootWindow->getChild("MainMenu/Options");
    optionsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuState::options, this));

    auto* exitButton = m_rootWindow->getChild("MainMenu/Exit");
    exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuState::exit, this));
}

bool MainMenuState::handleEvent(const sf::Event& e)
{
    return false;
}

void MainMenuState::update(float dt)
{

}

void MainMenuState::draw(sf::RenderWindow& window) const
{

}

void MainMenuState::onActive()
{
    //Now that we are the active state we have to tell CEGUI to use our root window, rather than the old one from the previous state
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_rootWindow);
}

void MainMenuState::onInactive()
{

}

bool MainMenuState::newGame(const CEGUI::EventArgs& e)
{
    m_galemp->getStateManager()->push<NewGameState>(m_galemp);
    return true;
}

bool MainMenuState::options(const CEGUI::EventArgs& e)
{
    m_galemp->getStateManager()->push<OptionsMenuState>(m_galemp);
    return true;
}

bool MainMenuState::exit(const CEGUI::EventArgs& e)
{
    m_galemp->getWindow()->close();
    return true;
}
