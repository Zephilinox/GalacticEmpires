#include "State/OptionsMenuState.hpp"

OptionsMenuState::OptionsMenuState(GalacticEmpires* galemp)
    : m_galemp(galemp)
    , m_guiWindow(sfg::Window::Create(sfg::Window::BACKGROUND))
{
    sf::Vector2u windowSize = m_galemp->getWindow()->getSize();

    auto boxMenu = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20.f);
    auto btnExit = sfg::Button::Create("Exit");
    btnExit->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&OptionsMenuState::exit, this));
    boxMenu->Pack(btnExit);

    m_guiWindow->Add(boxMenu);
    m_guiWindow->SetAllocation(sf::FloatRect(windowSize.x * 0.3, windowSize.y * 0.1, windowSize.x * 0.4, windowSize.y * 0.8));

    sfg::Desktop desk;
    desk.SetProperty("#MainMenuButton", "FontSize", 36);
    btnExit->SetId("MainMenuButton");
}

void OptionsMenuState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);
}

void OptionsMenuState::update(float dt)
{
    m_guiWindow->Update(dt);
}

void OptionsMenuState::draw(sf::RenderWindow& window) const
{

}

void OptionsMenuState::onActive()
{
    m_guiWindow->Show(true);
}

void OptionsMenuState::onInactive()
{
    m_guiWindow->Show(false);
}

void OptionsMenuState::exit()
{
    m_galemp->getStateManager()->pop();
}
