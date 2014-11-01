#include "State/MainMenuState.hpp"

MainMenuState::MainMenuState(GalacticEmpires* galpires)
    : m_galpires(galpires)
    , m_guiWindow(sfg::Window::Create(sfg::Window::BACKGROUND))
{
    sf::Vector2u windowSize = m_galpires->getWindow()->getSize();

    auto boxMenu = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20.f);
    auto btnNewGame = sfg::Button::Create("New Game");
    auto btnLoadGame = sfg::Button::Create("Load Game");
    auto btnOptions = sfg::Button::Create("Options");
    auto btnExit = sfg::Button::Create("Exit");

    btnNewGame->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::newGame, this));
    btnLoadGame->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::loadGame, this));
    btnOptions->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::options, this));
    btnExit->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::exit, this));

    boxMenu->Pack(btnNewGame);
    boxMenu->Pack(btnLoadGame);
    boxMenu->Pack(btnOptions);
    boxMenu->Pack(btnExit);

    m_guiWindow->Add(boxMenu);
    m_guiWindow->SetAllocation(sf::FloatRect(windowSize.x * 0.3, windowSize.y * 0.1, windowSize.x * 0.4, windowSize.y * 0.8));

    sfg::Desktop desk;
    desk.SetProperty("#MainMenuButton", "FontSize", 36);

    btnNewGame->SetId("MainMenuButton");
    btnLoadGame->SetId("MainMenuButton");
    btnOptions->SetId("MainMenuButton");
    btnExit->SetId("MainMenuButton");
}

void MainMenuState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);
}

void MainMenuState::update(float dt)
{
    m_guiWindow->Update(dt);
}

void MainMenuState::draw(sf::RenderWindow& window) const
{

}

void MainMenuState::onActive()
{
    m_guiWindow->Show(true);
}

void MainMenuState::onInactive()
{
    m_guiWindow->Show(false);
}
void MainMenuState::newGame()
{

}

void MainMenuState::loadGame()
{

}

void MainMenuState::options()
{

}

void MainMenuState::exit()
{
    m_galpires->getWindow()->close();
}
