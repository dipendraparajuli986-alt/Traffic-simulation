#pragma once
#include <SFML/Graphics.hpp>

class Renderer {
public:
    Renderer(sf::RenderWindow& window);
    void setPixel(int x, int y, sf::Color color);

private:
    sf::RenderWindow& m_window;
};