#include <SFML/Graphics.hpp>
#include "algorithms/DDA.h"
#include "algorithms/Bresenham.h"
#include "algorithms/MidpointCircle.h"
#include "algorithms/ScanlineFill.h"
#include "math/Vec3.h"
#include "math/Matrix4.h"
#include "engine/Projection.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Traffic Sim");

    Projection proj;

    Vec3 cubePoints[8] = {
        {-1, -1, 3}, { 1, -1, 3}, { 1,  1, 3}, {-1,  1, 3},
        {-1, -1, 5}, { 1, -1, 5}, { 1,  1, 5}, {-1,  1, 5}
    };

    int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    float angle = 0.0f;

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

        angle += 0.01f;
        Matrix4 rot = Matrix4::rotationY(angle);

        window.clear(sf::Color(30, 30, 30));

        for (auto& edge : edges)
        {
            Vec3 p1 = rot.transform(cubePoints[edge[0]]);
            Vec3 p2 = rot.transform(cubePoints[edge[1]]);

            Vec2 s1 = proj.project(p1);
            Vec2 s2 = proj.project(p2);

            Bresenham::drawLine(window, s1.x, s1.y, s2.x, s2.y, sf::Color::Green);
        }

        window.display();
    }

    return 0;
}