#pragma once
#include <SFML/Graphics.hpp>

class MidpointCircle {
        static void plotPoints(sf::RenderWindow& window, int cx, int cy, int x, int y, sf::Color color)
    {
        drawPixel(window, cx + x, cy + y, color);
        drawPixel(window, cx - x, cy + y, color);
        drawPixel(window, cx + x, cy - y, color);
        drawPixel(window, cx - x, cy - y, color);
        drawPixel(window, cx + y, cy + x, color);
        drawPixel(window, cx - y, cy + x, color);
        drawPixel(window, cx + y, cy - x, color);
        drawPixel(window, cx - y, cy - x, color);
    }

    static void drawPixel(sf::RenderWindow& window, int x, int y, sf::Color color)
    {
        sf::RectangleShape pixel(sf::Vector2f(1.0f, 1.0f));
        pixel.setPosition(sf::Vector2f((float)x, (float)y));
        pixel.setFillColor(color);
        window.draw(pixel);
    }
public:
    static void drawCircle(sf::RenderWindow& window, int cx, int cy, int radius, sf::Color color)
    {
        int x = 0;
        int y = radius;
        int d = 1 - radius;

        plotPoints(window, cx, cy, x, y, color);

        while (x < y)
        {
            if (d < 0)
            {
                d += 2 * x + 3;
            }
            else
            {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
            plotPoints(window, cx, cy, x, y, color);
        }
    }
};