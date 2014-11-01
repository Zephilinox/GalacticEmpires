#include "States/MainMenuState.hpp"

//STD
#include <iostream>

//3RD

//SELF

MainMenuState::MainMenuState(sf::RenderWindow& window, zge::StateCollection& stateCollection)
    : BaseState(window, stateCollection)
    , m_guiMainMenu(sfg::Window::Create(sfg::Window::BACKGROUND))
    , m_exit(false)
{
    m_stateID = "MainMenuState";

    sfg::Box::Ptr box(sfg::Box::Create(sfg::Box::Orientation::VERTICAL));
    auto btnNewGame(sfg::Button::Create("New Game"));
    sfg::Button::Ptr btnLoadGame(sfg::Button::Create("Load Game"));
    sfg::Button::Ptr btnOptions(sfg::Button::Create("Options"));
    sfg::Button::Ptr btnExit(sfg::Button::Create("Exit"));

    btnNewGame->SetId("MainMenuButton");
    btnLoadGame->SetId("MainMenuButton");
    btnOptions->SetId("MainMenuButton");
    btnExit->SetId("MainMenuButton");
    btnExit->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::exit, this));

    sfg::Desktop desk;
    desk.SetProperty("#MainMenuButton", "FontSize", 36);

    box->SetSpacing(20.f);
    box->Pack(btnNewGame);
    box->Pack(btnLoadGame);
    box->Pack(btnOptions);
    box->Pack(btnExit);
    m_guiMainMenu->Add(box);
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
    if (m_exit)
    {
        m_stateCollection.pop();
    }
}

void MainMenuState::exit()
{
    std::cout << "Exiting\n";
    m_exit = true;
}
