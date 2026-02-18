#include <SFML/Graphics.hpp>
#include "algorithms/DDA.h"
#include "algorithms/Bresenham.h"
#include "algorithms/MidpointCircle.h"
#include "algorithms/ScanlineFill.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Traffic Sim");

    std::vector<sf::Vector2f> carShape = {
        {300, 200},
        {500, 200},
        {500, 300},
        {300, 300}
    };
    
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
        Bresenham :: drawLine(window , 100,200,700,400 , sf::Color::Yellow);
        MidpointCircle::drawCircle(window, 400, 300, 80, sf::Color::Red);
        ScanlineFill::fillPolygon(window, carShape, sf::Color::Blue);
        window.display();
    }

    return 0;
}