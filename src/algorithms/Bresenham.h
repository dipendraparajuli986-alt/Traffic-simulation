#pragma once
#include <SFML/Graphics.hpp>

class Bresenham {
public:
    static void drawLine(sf::RenderWindow& window, int x1, int y1, int x2, int y2, sf::Color color)
    {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);

        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;

        int err = dx - dy; 

        while (true)
        {
            sf::RectangleShape pixel(sf::Vector2f(1.0f, 1.0f));
            pixel.setPosition(sf::Vector2f((float)x1, (float)y1));
            pixel.setFillColor(color);
            window.draw(pixel);

            if (x1 == x2 && y1 == y2) break;

            int e2 = 2 * err;
            
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 <  dx) { err += dx; y1 += sy; }
        }
    }
};