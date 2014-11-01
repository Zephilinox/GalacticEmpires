#include "TestState.hpp"

//STD
#include <cmath>
#include <iostream>

//3RD

//SELF

TestState::TestState(GalacticEmpires* galpires)
    : m_galpires(galpires)
    , rs(sf::Vector2f(std::rand()%200, std::rand()%200))
    , m_hasShat(false)
    , m_guiWindow(sfg::Window::Create())
    , m_guiBtn(sfg::Button::Create("Clickz"))
{
    m_guiBtn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&TestState::doShit, this));
    m_guiWindow->Add(m_guiBtn);
    rs.setFillColor(sf::Color(std::rand()%255, std::rand()%255, std::rand()%255));
}

void TestState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);

    switch(e.type)
    {
        default:
        {
            break;
        }
    }
}

void TestState::update(float dt)
{
    m_guiWindow->Update(dt);

    rs.move(1*dt, 1*dt);
}

void TestState::draw(sf::RenderWindow& window) const
{
    if (!m_hasShat)
    {
        window.draw(rs);
    }
}

void TestState::doShit()
{
    m_hasShat = true;
}
