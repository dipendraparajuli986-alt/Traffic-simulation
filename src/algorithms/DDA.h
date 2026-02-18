#pragma once
#include <SFML/Graphics.hpp>

class DDA {
public:
    static void drawLine(sf::RenderWindow& window, int x1, int y1, int x2, int y2, sf::Color color)
    {
        int dx = x2 - x1;
        int dy = y2 - y1;

        int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

        float xIncrement = (float)dx / steps;
        float yIncrement = (float)dy / steps;

        float x = x1;
        float y = y1;

        for (int i = 0; i <= steps; i++)
        {
            sf::RectangleShape pixel(sf::Vector2f(1.0f, 1.0f));
            pixel.setPosition(sf::Vector2f(x, y));
            pixel.setFillColor(color);
            window.draw(pixel);

            x += xIncrement;
            y += yIncrement;
        }
    }
};