#include <SFML/Graphics.hpp>
#include "algorithms/DDA.h"
#include "algorithms/Bresenham.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Traffic Sim");

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (auto* key = event->getIf<sf::Event::KeyPressed>())
                if (key->code == sf::Keyboard::Key::Escape)
                    window.close();
        }

        window.clear(sf::Color(30, 30, 30));
        
        DDA::drawLine(window, 100,100,700,500, sf::Color::White);
        
        window.display();
    }

    return 0;
}