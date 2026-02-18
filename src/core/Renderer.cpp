#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& window)
    : m_window(window)
{
}

void Renderer::setPixel(int x, int y, sf::Color color)
{
    sf::RectangleShape pixel(sf::Vector2f(1.0f, 1.0f));
    pixel.setPosition(sf::Vector2f((float)x, (float)y));
    pixel.setFillColor(color);
    m_window.draw(pixel);
}