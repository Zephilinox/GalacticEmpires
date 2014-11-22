#include "State/OptionsMenuState.hpp"

#include "Helper/Utility.hpp"

OptionsMenuState::OptionsMenuState(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    m_rootWindow = wmgr.loadLayoutFromFile("OptionsMenu.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_rootWindow);

    auto* btnApply = m_rootWindow->getChild("OptionsMenu/Apply");
    auto* btnOkay = m_rootWindow->getChild("OptionsMenu/Okay");
    btnApply->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OptionsMenuState::applyChanges, this));
    btnOkay->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&OptionsMenuState::saveChanges, this));

    auto* ebWidthValue = m_rootWindow->getChild("OptionsMenu/WidthValue");
    auto* ebHeightValue = m_rootWindow->getChild("OptionsMenu/HeightValue");
    ebWidthValue->setText(CEGUI::String(toString(m_galemp->getSettings()->getInt("width", "Video"))));
    ebHeightValue->setText(CEGUI::String(toString(m_galemp->getSettings()->getInt("height", "Video"))));
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
    auto* ebWidthValue = m_rootWindow->getChild("OptionsMenu/WidthValue");
    auto* ebHeightValue = m_rootWindow->getChild("OptionsMenu/HeightValue");
    ebWidthValue->setText(CEGUI::String(toString(m_galemp->getSettings()->getInt("width", "Video"))));
    ebHeightValue->setText(CEGUI::String(toString(m_galemp->getSettings()->getInt("height", "Video"))));
}

void OptionsMenuState::onInactive()
{
}

void OptionsMenuState::exit()
{
    m_galemp->getStateManager()->pop();
}

bool OptionsMenuState::applyChanges(const CEGUI::EventArgs& e)
{
    auto* ebWidthValue = m_rootWindow->getChild("OptionsMenu/WidthValue");
    auto* ebHeightValue = m_rootWindow->getChild("OptionsMenu/HeightValue");

    m_galemp->getSettings()->setValue("width", fromString<int>(ebWidthValue->getText().c_str()), "Video");
    m_galemp->getSettings()->setValue("height", fromString<int>(ebHeightValue->getText().c_str()), "Video");
}

bool OptionsMenuState::saveChanges(const CEGUI::EventArgs& e)
{
    m_galemp->getSettings()->save();
}
