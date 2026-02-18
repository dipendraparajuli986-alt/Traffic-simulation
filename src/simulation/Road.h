#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"

struct Road {
    Vec3 start;
    Vec3 end;
    float width;

    Road(Vec3 start, Vec3 end, float width = 0.5f)
        : start(start), end(end), width(width) {}

    void draw(Renderer& renderer) {
        Vec3 dir = (end - start).normalize();

        Vec3 perp = {-dir.z, 0, dir.x};

        Vec3 p1 = start + perp * width;
        Vec3 p2 = start - perp * width;
        Vec3 p3 = end   - perp * width;
        Vec3 p4 = end   + perp * width;

        Vec2 s1 = renderer.project(p1);
        Vec2 s2 = renderer.project(p2);
        Vec2 s3 = renderer.project(p3);
        Vec2 s4 = renderer.project(p4);

        std::vector<sf::Vector2f> surface = {
            {s1.x, s1.y}, {s2.x, s2.y},
            {s3.x, s3.y}, {s4.x, s4.y}
        };

        renderer.fillPolygon(surface, sf::Color(80, 80, 80));

        renderer.drawLine(s1, s4, sf::Color::White);
        renderer.drawLine(s2, s3, sf::Color::Red);
    }
};