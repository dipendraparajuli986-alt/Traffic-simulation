#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"
#include <vector>
#include <cmath>

struct Background {

    void drawSky(sf::RenderWindow& window, int screenW, float horizonY) {
        for (int y = 0; y < horizonY; y++) {
            float t = (float)y / horizonY;
            sf::Color top    = sf::Color(20,  40,  80);
            sf::Color bottom = sf::Color(100, 140, 180);
            sf::Color color  = sf::Color(
                top.r + t * (bottom.r - top.r),
                top.g + t * (bottom.g - top.g),
                top.b + t * (bottom.b - top.b)
            );
            sf::RectangleShape line(sf::Vector2f(screenW, 1));
            line.setPosition(sf::Vector2f(0, y));
            line.setFillColor(color);
            window.draw(line);
        }
    }

    void drawGrass(sf::RenderWindow& window, int screenW, int screenH, float horizonY) {
        sf::RectangleShape grass(sf::Vector2f(screenW, screenH - horizonY));
        grass.setPosition(sf::Vector2f(0, horizonY));
        grass.setFillColor(sf::Color(34, 100, 34));
        window.draw(grass);
    }

    void drawMountains(sf::RenderWindow& window, int screenW, int screenH) {
        struct BezierMountain {
            float x1, y1, x2, y2, x3, y3, x4, y4;
            sf::Color color;
        };

        BezierMountain mountains[] = {
    {0,    350, 100, 100, 300, 100, 400, 350, sf::Color(60,  80,  60)},
    {200,  350, 350,  50, 550,  50, 700, 350, sf::Color(50,  70,  50)},
    {500,  350, 650, 130, 850, 130, 1000,350, sf::Color(70,  90,  70)},
    {800,  350, 950,  70, 1100, 70, 1200,350, sf::Color(55,  75,  55)},
    {-100, 350,  50, 150, 250, 150,  350, 350, sf::Color(65,  85,  65)}
};
        for (auto& m : mountains) {
            std::vector<sf::Vector2f> points;
            points.push_back({m.x1, m.y1});

            for (float t = 0; t <= 1; t += 0.01f) {
                float xt = pow(1-t,3)*m.x1 +
                           3*t*pow(1-t,2)*m.x2 +
                           3*t*t*(1-t)*m.x3 +
                           pow(t,3)*m.x4;
                float yt = pow(1-t,3)*m.y1 +
                           3*t*pow(1-t,2)*m.y2 +
                           3*t*t*(1-t)*m.y3 +
                           pow(t,3)*m.y4;
                points.push_back({xt, yt});
            }
            points.push_back({m.x4, m.y4});

            float minY = points[0].y, maxY = points[0].y;
            for (auto& p : points) {
                if (p.y < minY) minY = p.y;
                if (p.y > maxY) maxY = p.y;
            }

            for (float y = minY; y <= maxY; y++) {
                std::vector<float> intersections;
                int n = points.size();
                for (int i = 0; i < n - 1; i++) {
                    sf::Vector2f p1 = points[i];
                    sf::Vector2f p2 = points[i + 1];
                    if ((p1.y <= y && p2.y > y) || (p2.y <= y && p1.y > y)) {
                        float x = p1.x + (y - p1.y) / (p2.y - p1.y) * (p2.x - p1.x);
                        intersections.push_back(x);
                    }
                }
                std::sort(intersections.begin(), intersections.end());
                for (int i = 0; i + 1 < (int)intersections.size(); i += 2) {
                    sf::RectangleShape line(sf::Vector2f(intersections[i+1] - intersections[i], 1));
                    line.setPosition(sf::Vector2f(intersections[i], y));
                    line.setFillColor(m.color);
                    window.draw(line);
                }
            }
        }
    }

    void draw(sf::RenderWindow& window, Renderer& renderer, int screenW, int screenH, float horizonY) {
        drawSky(window, screenW, horizonY);
        drawMountains(window, screenW, screenH);
        drawGrass(window, screenW, screenH, horizonY);
    }
};