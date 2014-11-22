#include "Graphics/TextHandler.hpp"

#include <exception>

TextHandler::TextHandler(std::string textString, std::string fontLocation, unsigned characterSize, sf::Vector2f position, Origin origin)
    : m_position(position)
    , m_origin(origin)
    , m_borderEnabled(false)
    , m_borderColor(sf::Color::Black)
{
    m_font.loadFromFile(fontLocation);
    m_text.setFont(m_font);
    m_text.setString(textString);
    m_text.setCharacterSize(characterSize);

    updatePosition();
}

bool TextHandler::handleEvent(const sf::Event& event)
{
    return false;
}

void TextHandler::update(float dt)
{
    updatePosition();
}

void TextHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_borderEnabled)
    {
        sf::Vector2f pos = m_text.getPosition();
        sf::Text text = m_text;

        //We need to use the alpha of the original text so that the border can fade along with it.
        text.setColor(sf::Color(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_text.getColor().a));

        text.setPosition(pos.x - 1, pos.y);
        target.draw(text, states);

        text.setPosition(pos.x + 1, pos.y);
        target.draw(text, states);

        text.setPosition(pos.x, pos.y - 1);
        target.draw(text, states);

        text.setPosition(pos.x, pos.y + 1);
        target.draw(text, states);

        target.draw(m_text, states);
    }
    else
    {
        target.draw(m_text, states);
    }
}

void TextHandler::setText(std::string str)
{
    m_text.setString(str);
}

void TextHandler::setColor(sf::Color col)
{
    m_text.setColor(col);
}

void TextHandler::setBorderEnabled(bool enable)
{
    m_borderEnabled = enable;
}

void TextHandler::setBorderColor(sf::Color col)
{
    m_borderColor = col;
}

void TextHandler::setPosition(sf::Vector2f pos)
{
    m_position = pos;
    updatePosition();
}

void TextHandler::setOrigin(Origin ori)
{
    m_origin = ori;
    updatePosition();
}

sf::Color TextHandler::getColor()
{
    return m_text.getColor();
}

void TextHandler::updatePosition()
{
    switch(m_origin)
    {
        // +/- 1 is for a bit of padding around the corners of the screen

        case Origin::TopLeft:
        {
            m_text.setPosition(m_position.x - m_text.getLocalBounds().left + 1,
                               m_position.y - m_text.getLocalBounds().top + 1);
            break;
        }

        case Origin::TopRight:
        {
            m_text.setPosition(m_position.x - (m_text.getLocalBounds().width + m_text.getLocalBounds().left) - 1,
                               m_position.y - m_text.getLocalBounds().top + 1);
            break;
        }

        case Origin::TopCentre:
        {
            m_text.setPosition(m_position.x - ((m_text.getLocalBounds().width + m_text.getLocalBounds().left)/2),
                               m_position.y - m_text.getLocalBounds().top + 1);
            break;
        }

        case Origin::BottomLeft:
        {
            m_text.setPosition(m_position.x - m_text.getLocalBounds().left + 1,
                               m_position.y - (m_text.getLocalBounds().height + m_text.getLocalBounds().top) - 1);
            break;
        }

        case Origin::BottomRight:
        {
            m_text.setPosition(m_position.x - (m_text.getLocalBounds().width + m_text.getLocalBounds().left) - 1,
                               m_position.y - (m_text.getLocalBounds().height + m_text.getLocalBounds().top) - 1);
            break;
        }

        case Origin::BottomCentre:
        {
            m_text.setPosition(m_position.x - ((m_text.getLocalBounds().width + m_text.getLocalBounds().left)/2),
                               m_position.y - (m_text.getLocalBounds().height + m_text.getLocalBounds().top) - 1);
            break;
        }

        case Origin::MiddleCentre:
        {
            m_text.setPosition(m_position.x - ((m_text.getLocalBounds().width + m_text.getLocalBounds().left)/2),
                               m_position.y - ((m_text.getLocalBounds().height + m_text.getLocalBounds().top))/2);
            break;
        }

        default:
        {
            throw std::runtime_error("That origin type is invalid");
        }
    }
}
