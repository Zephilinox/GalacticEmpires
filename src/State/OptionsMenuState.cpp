#include "State/OptionsMenuState.hpp"

OptionsMenuState::OptionsMenuState(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    m_rootWindow = wmgr.loadLayoutFromFile("OptionsMenu.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_rootWindow);

    CEGUI::MultiColumnList* mcl = static_cast<CEGUI::MultiColumnList*>(m_rootWindow->getChild("OptionsMenu/OptionsList"));

    mcl->addColumn(CEGUI::String("Option"), 0, CEGUI::UDim(0.45f, 0.f));
    mcl->addColumn(CEGUI::String("Value"), 1, CEGUI::UDim(0.45f, 0.f));
}

bool OptionsMenuState::handleEvent(const sf::Event& e)
{
    return false;
}

void OptionsMenuState::update(float dt)
{
}

void OptionsMenuState::draw(sf::RenderWindow& window) const
{

}

void OptionsMenuState::onActive()
{
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_rootWindow);
}

void OptionsMenuState::onInactive()
{
}

void OptionsMenuState::exit()
{
    m_galemp->getStateManager()->pop();
}
