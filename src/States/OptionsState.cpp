#include "States/OptionsState.hpp"

//STD

//3RD
#include <ini_parser.hpp>

//SELF

OptionsState::OptionsState(sf::RenderWindow* window, zge::StateCollection* stateCollection)
    : BaseState(window, stateCollection)
    , m_guiWindow(sfg::Window::Create(sfg::Window::BACKGROUND))
    , m_works(false)
{
    m_stateID = "OptionsState";

    ini_parser iniParser("data/settings.ini");

    sfg::Notebook::Ptr notebook = sfg::Notebook::Create();
    sfg::Box::Ptr box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    sfg::Box::Ptr box2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    sfg::Box::Ptr box3 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    sfg::Box::Ptr box4 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    sfg::Box::Ptr box5 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    sfg::Box::Ptr box6 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    sfg::Box::Ptr box7 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    sfg::Box::Ptr box8 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

    sfg::Entry::Ptr enterWidth = sfg::Entry::Create(std::to_string(iniParser.get_int("width", "Video")));
    sfg::Entry::Ptr enterHeight = sfg::Entry::Create(std::to_string(iniParser.get_int("height", "Video")));
    sfg::Entry::Ptr enterBits = sfg::Entry::Create(std::to_string(iniParser.get_int("bitDepth", "Video")));
    sfg::Entry::Ptr enterMaxFPS = sfg::Entry::Create(std::to_string(iniParser.get_int("maxFPS", "Video")));

    sfg::CheckButton::Ptr enterFullscreen = sfg::CheckButton::Create("");
    sfg::CheckButton::Ptr enterVSync = sfg::CheckButton::Create("");
    enterFullscreen->SetActive(iniParser.get_bool("fullscreen", "Video"));
    enterVSync->SetActive(iniParser.get_bool("vsync", "Video"));

    sfg::Label::Ptr lblWidth = sfg::Label::Create("Window Width: ");
    sfg::Label::Ptr lblHeight = sfg::Label::Create("Window Height: ");
    sfg::Label::Ptr lblBits = sfg::Label::Create("Window Bits Per Pixel: ");
    sfg::Label::Ptr lblFullscreen = sfg::Label::Create("Window Fullscreen: ");
    sfg::Label::Ptr lblVSync = sfg::Label::Create("Window Vertical Sync: ");
    sfg::Label::Ptr lblMaxFPS = sfg::Label::Create("Window Max FPS: ");

    sfg::Button::Ptr btnDefault = sfg::Button::Create("Reset to Default");
    sfg::Button::Ptr btnApply = sfg::Button::Create("Apply");
    std::cout << this << " " << m_stateID << "\n";
    btnDefault->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&OptionsState::loadDefaults, this));
    std::cout << this << " " << m_stateID << "\n";
    sfg::Separator::Ptr sprSettings1 = sfg::Separator::Create();
    sfg::Separator::Ptr sprSettings2 = sfg::Separator::Create();
    sfg::Separator::Ptr sprSettings3 = sfg::Separator::Create();
    sfg::Separator::Ptr sprSettings4 = sfg::Separator::Create();
    sfg::Separator::Ptr sprSettings5 = sfg::Separator::Create();
    sfg::Separator::Ptr sprSettings6 = sfg::Separator::Create();

    box2->Pack(lblWidth);
    box2->Pack(enterWidth);

    box3->Pack(lblHeight);
    box3->Pack(enterHeight);

    box4->Pack(lblBits);
    box4->Pack(enterBits);

    box5->Pack(lblFullscreen);
    box5->Pack(enterFullscreen);

    box6->Pack(lblVSync);
    box6->Pack(enterVSync);

    box7->Pack(lblMaxFPS);
    box7->Pack(enterMaxFPS);

    box8->Pack(btnDefault);
    box8->Pack(btnApply);

    box->SetSpacing(20.0f);
    box->Pack(box2);
    box->Pack(sprSettings1);
    box->Pack(box3);
    box->Pack(sprSettings2);
    box->Pack(box4);
    box->Pack(sprSettings3);
    box->Pack(box5);
    box->Pack(sprSettings4);
    box->Pack(box6);
    box->Pack(sprSettings5);
    box->Pack(box7);
    box->Pack(sprSettings6);
    box->Pack(box8);
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
    if (m_works) std::cout << "yay\n"; //doesn't work
}

void OptionsState::loadDefaults()
{
    std::cout << "hi " << this << " " << (*this).m_stateID << "\n";
    m_works = true; //lies
}
