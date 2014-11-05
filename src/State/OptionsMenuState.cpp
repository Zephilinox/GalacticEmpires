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

    auto settingsLabel1Alignment = sfg::Alignment::Create();
    auto settingsLabel2Alignment = sfg::Alignment::Create();
    auto settingsLabel3Alignment = sfg::Alignment::Create();
    auto settingsLabel4Alignment = sfg::Alignment::Create();
    auto settingsLabel5Alignment = sfg::Alignment::Create();
    auto settingsLabel6Alignment = sfg::Alignment::Create();

    auto settingsLabel1 = sfg::Label::Create("Width");
    auto settingsLabel2 = sfg::Label::Create("Height");
    auto settingsLabel3 = sfg::Label::Create("Bit Depth");
    auto settingsLabel4 = sfg::Label::Create("Fullscreen");
    auto settingsLabel5 = sfg::Label::Create("V-Sync");
    auto settingsLabel6 = sfg::Label::Create("MaxFPS");

    auto settingsModifier1Alignment = sfg::Alignment::Create();
    auto settingsModifier2Alignment = sfg::Alignment::Create();
    auto settingsModifier3Alignment = sfg::Alignment::Create();
    auto settingsModifier4Alignment = sfg::Alignment::Create();
    auto settingsModifier5Alignment = sfg::Alignment::Create();
    auto settingsModifier6Alignment = sfg::Alignment::Create();

    auto settingsModifier1 = sfg::Entry::Create();
    auto settingsModifier2 = sfg::Entry::Create();
    auto settingsModifier3 = sfg::Entry::Create();
    auto settingsModifier4 = sfg::CheckButton::Create("");
    auto settingsModifier5 = sfg::CheckButton::Create("");
    auto settingsModifier6 = sfg::Entry::Create();

    settingsLabel1Alignment->Add(settingsLabel1);
    settingsModifier1Alignment->Add(settingsModifier1);
    settingsBox1->Pack(settingsLabel1Alignment);
    settingsBox1->Pack(settingsModifier1Alignment);

    settingsLabel2Alignment->Add(settingsLabel2);
    settingsModifier2Alignment->Add(settingsModifier2);
    settingsBox2->Pack(settingsLabel2Alignment);
    settingsBox2->Pack(settingsModifier2Alignment);

    settingsLabel3Alignment->Add(settingsLabel3);
    settingsModifier3Alignment->Add(settingsModifier3);
    settingsBox3->Pack(settingsLabel3Alignment);
    settingsBox3->Pack(settingsModifier3Alignment);

    settingsLabel4Alignment->Add(settingsLabel4);
    settingsModifier4Alignment->Add(settingsModifier4);
    settingsBox4->Pack(settingsLabel4Alignment);
    settingsBox4->Pack(settingsModifier4Alignment);

    settingsLabel5Alignment->Add(settingsLabel5);
    settingsModifier5Alignment->Add(settingsModifier5);
    settingsBox5->Pack(settingsLabel5Alignment);
    settingsBox5->Pack(settingsModifier5Alignment);

    settingsLabel6Alignment->Add(settingsLabel6);
    settingsModifier6Alignment->Add(settingsModifier6);
    settingsBox6->Pack(settingsLabel6Alignment);
    settingsBox6->Pack(settingsModifier6Alignment);

    videoSettingsPage->Pack(settingsBox1);
    videoSettingsPage->Pack(settingsBox2);
    videoSettingsPage->Pack(settingsBox3);
    videoSettingsPage->Pack(settingsBox4);
    videoSettingsPage->Pack(settingsBox5);
    videoSettingsPage->Pack(settingsBox6);

    notebook->AppendPage(videoSettingsPage, sfg::Label::Create("Video"));
    optionsMenuBox->Pack(notebook);
    optionsMenuBox->Pack(btnExit);
    m_guiWindow->Add(optionsMenuBox);

    btnExit->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&OptionsMenuState::exit, this));

    settingsLabel1Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsLabel1Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));
    settingsModifier1Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsModifier1Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));

    settingsLabel2Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsLabel2Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));
    settingsModifier2Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsModifier2Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));

    settingsLabel3Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsLabel3Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));
    settingsModifier3Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsModifier3Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));

    settingsLabel4Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsLabel4Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));
    settingsModifier4Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsModifier4Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));

     settingsLabel5Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsLabel5Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));
    settingsModifier5Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsModifier5Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));

    settingsLabel6Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsLabel6Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));
    settingsModifier6Alignment->SetScale(sf::Vector2f(1.0f, 0.0f));
    settingsModifier6Alignment->SetAlignment(sf::Vector2f(0.00f, 0.5f));

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
