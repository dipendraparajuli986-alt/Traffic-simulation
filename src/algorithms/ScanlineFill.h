#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class ScanlineFill {
public:
    static void fillPolygon(sf::RenderWindow& window, std::vector<sf::Vector2f> points, sf::Color color)
    {
        if (points.size() < 3) return; 
        float minY = points[0].y;
        float maxY = points[0].y;
        for (auto& p : points)
        {
            if (p.y < minY) minY = p.y;
            if (p.y > maxY) maxY = p.y;
        }

        for (float y = minY; y <= maxY; y++)
        {
            std::vector<float> intersections;

            int n = points.size();
            for (int i = 0; i < n; i++)
            {
                sf::Vector2f p1 = points[i];
                sf::Vector2f p2 = points[(i + 1) % n];

                if ((p1.y <= y && p2.y > y) || (p2.y <= y && p1.y > y))
                {
                    float x = p1.x + (y - p1.y) / (p2.y - p1.y) * (p2.x - p1.x);
                    intersections.push_back(x);
                }
            }

            std::sort(intersections.begin(), intersections.end());

            for (int i = 0; i + 1 < intersections.size(); i += 2)
            {
                float xStart = intersections[i];
                float xEnd   = intersections[i + 1];

                for (float x = xStart; x <= xEnd; x++)
                {
                    sf::RectangleShape pixel(sf::Vector2f(1.0f, 1.0f));
                    pixel.setPosition(sf::Vector2f(x, y));
                    pixel.setFillColor(color);
                    window.draw(pixel);
                }
            }
        }
    }
};