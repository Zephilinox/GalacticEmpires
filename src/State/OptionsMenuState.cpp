#include "State/OptionsMenuState.hpp"

OptionsMenuState::OptionsMenuState(GalacticEmpires* galemp)
    : m_galemp(galemp)
    , m_guiWindow(sfg::Window::Create(sfg::Window::BACKGROUND))
{
    auto optionsMenuBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    auto notebook = sfg::Notebook::Create();
    auto btnExit = sfg::Button::Create("Exit");

    auto videoSettingsPage = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

    auto settingsBox1 = sfg::Box::Create();
    auto settingsBox2 = sfg::Box::Create();
    auto settingsBox3 = sfg::Box::Create();
    auto settingsBox4 = sfg::Box::Create();
    auto settingsBox5 = sfg::Box::Create();
    auto settingsBox6 = sfg::Box::Create();

    auto settingsLabel1 = sfg::Label::Create("Width");
    auto settingsLabel2 = sfg::Label::Create("Height");
    auto settingsLabel3 = sfg::Label::Create("Bit Depth");
    auto settingsLabel4 = sfg::Label::Create("Fullscreen");
    auto settingsLabel5 = sfg::Label::Create("V-Sync");
    auto settingsLabel6 = sfg::Label::Create("MaxFPS");

    auto settingsModifier1 = sfg::Entry::Create();
    auto settingsModifier2 = sfg::Entry::Create();
    auto settingsModifier3 = sfg::Entry::Create();
    auto settingsModifier4 = sfg::CheckButton::Create("");
    auto settingsModifier5 = sfg::CheckButton::Create("");
    auto settingsModifier6 = sfg::Entry::Create();

    settingsBox1->Pack(settingsLabel1);
    settingsBox1->Pack(settingsModifier1);

    settingsBox2->Pack(settingsLabel2);
    settingsBox2->Pack(settingsModifier2);

    settingsBox2->Pack(settingsLabel3);
    settingsBox2->Pack(settingsModifier3);

    settingsBox3->Pack(settingsLabel3);
    settingsBox3->Pack(settingsModifier3);

    settingsBox4->Pack(settingsLabel4);
    settingsBox4->Pack(settingsModifier4);

    settingsBox5->Pack(settingsLabel5);
    settingsBox5->Pack(settingsModifier5);

    settingsBox5->Pack(settingsLabel5);
    settingsBox5->Pack(settingsModifier5);

    settingsBox6->Pack(settingsLabel6);
    settingsBox6->Pack(settingsModifier6);

    sfg::Box::Ptr bx = sfg::Box::Create();
    sfg::Alignment::Ptr ali = sfg::Alignment::Create();
    bx->Pack(ali);
    ali->Add(sfg::Label::Create("test"));
    ali->SetScale(sf::Vector2f(0.f, 0.f));
    ali->SetAlignment(sf::Vector2f(1.f, 0.f));

    videoSettingsPage->Pack(settingsBox1);
    videoSettingsPage->Pack(settingsBox2);
    videoSettingsPage->Pack(settingsBox3);
    videoSettingsPage->Pack(settingsBox4);
    videoSettingsPage->Pack(settingsBox5);
    videoSettingsPage->Pack(settingsBox6);
    videoSettingsPage->Pack(bx);

    notebook->AppendPage(videoSettingsPage, sfg::Label::Create("Video"));
    optionsMenuBox->Pack(notebook);
    optionsMenuBox->Pack(btnExit);
    m_guiWindow->Add(optionsMenuBox);

    btnExit->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&OptionsMenuState::exit, this));

    sf::Vector2u windowSize = m_galemp->getWindow()->getSize();
    m_guiWindow->SetAllocation(sf::FloatRect(windowSize.x * 0.3, windowSize.y * 0.1, windowSize.x * 0.4, windowSize.y * 0.8));
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
