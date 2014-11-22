#ifndef TEXTHANDLER_HPP
#define TEXTHANDLER_HPP

#include <SFML/Graphics.hpp>

class TextHandler: public sf::Drawable
{
public:
    enum Origin {TopLeft, TopCentre, TopRight, MiddleLeft, MiddleCentre, MiddleRight, BottomLeft, BottomCentre, BottomRight};

    TextHandler(std::string textString, std::string fontLocation, unsigned characterSize, sf::Vector2f position, Origin origin);
    bool handleEvent(const sf::Event& event);
    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setText(std::string str);
    void setColor(sf::Color col);
    void setBorderEnabled(bool enable);
    void setBorderColor(sf::Color col);
    void setPosition(sf::Vector2f pos);
    void setOrigin(Origin ori);

    sf::Color getColor();

private:
    void updatePosition();

    sf::Font m_font;
    sf::Text m_text;
    sf::Vector2f m_position;
    Origin m_origin;

    bool m_borderEnabled;
    sf::Color m_borderColor;
};

#endif //TEXTHANDLER_HPP
