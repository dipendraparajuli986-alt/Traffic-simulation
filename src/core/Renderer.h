#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../math/Vec2.h"
#include "../math/Vec3.h"
#include "../engine/Projection.h"
#include "../engine/Camera.h"
#include "../algorithms/Bresenham.h"
#include "../algorithms/DDA.h"
#include "../algorithms/MidpointCircle.h"
#include "../algorithms/ScanlineFill.h"

class Renderer {
public:
    Renderer(sf::RenderWindow& window);

    void clear(sf::Color color = sf::Color(30, 30, 30));
    void display();

    void drawLine(Vec2 p1, Vec2 p2, sf::Color color);
    void drawCircle(int cx, int cy, int radius, sf::Color color);
    void fillPolygon(std::vector<sf::Vector2f> points, sf::Color color);

    Vec2 project(const Vec3& point);

    Camera camera;

private:
    sf::RenderWindow& m_window;
    Projection m_proj;
};