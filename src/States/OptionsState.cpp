#include "States/OptionsState.hpp"

//STD

//3RD
#include <ini_parser.hpp>

//SELF

OptionsState::OptionsState(sf::RenderWindow& window, zge::StateCollection& stateCollection)
    : BaseState(window, stateCollection)
    , m_guiWindow(sfg::Window::Create(sfg::Window::BACKGROUND))
{
    m_stateID = "OptionsState";

    ini_parser iniParser("data/settings.ini");

    sfg::Notebook::Ptr notebook = sfg::Notebook::Create();
    sfg::Entry::Ptr enterWidth = sfg::Entry::Create(std::to_string(iniParser.get_int("width", "Video")));
    sfg::Box::Ptr box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

    notebook->AppendPage(box, sfg::Label::Create("Video"));
    m_guiWindow->Add(notebook);
    m_guiWindow->SetAllocation(sf::FloatRect(1280/4, 720/8, 1280/2, 720 - 720/4));
}

void OptionsState::handleEvent(const sf::Event& event)
{
    m_guiWindow->HandleEvent(event);
}

void OptionsState::update(float dt)
{
    m_guiWindow->Update(dt);
}

void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void OptionsState::postDraw()
{
}
