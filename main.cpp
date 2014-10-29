//STD
#include <iostream>

//3RD
#include <SFML/Graphics.hpp>

//SELF

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Galactic Empires");

    sf::Clock frameTime;
    sf::Time prevFrameTime = sf::seconds(1.f/60.f);
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            switch (e.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }

                default:
                {
                    break;
                }
            }
        }

        window.clear(sf::Color(40, 40, 40));
        window.display();

        prevFrameTime = frameTime.getElapsedTime();
        frameTime.restart();
    }
}


