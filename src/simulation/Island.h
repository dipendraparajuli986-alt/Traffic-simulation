#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"

struct Island {
    Vec3 a, b, c;

    Island(Vec3 a, Vec3 b, Vec3 c) : a(a), b(b), c(c) {}

    void draw(Renderer& renderer) {
        Vec2 sa = renderer.project(a);
        Vec2 sb = renderer.project(b);
        Vec2 sc = renderer.project(c);

        std::vector<sf::Vector2f> triangle = {
            {sa.x, sa.y},
            {sb.x, sb.y},
            {sc.x, sc.y}
        };
        renderer.fillPolygon(triangle, sf::Color(34, 139, 34));

        renderer.drawLine(sa, sb, sf::Color(20, 100, 20));
        renderer.drawLine(sb, sc, sf::Color(20, 100, 20));
        renderer.drawLine(sc, sa, sf::Color(20, 100, 20));

        Vec2 center = {
            (sa.x + sb.x + sc.x) / 3.0f,
            (sa.y + sb.y + sc.y) / 3.0f
        };

        std::vector<sf::Vector2f> innerTriangle = {
            {sa.x * 0.3f + center.x * 0.7f, sa.y * 0.3f + center.y * 0.7f},
            {sb.x * 0.3f + center.x * 0.7f, sb.y * 0.3f + center.y * 0.7f},
            {sc.x * 0.3f + center.x * 0.7f, sc.y * 0.3f + center.y * 0.7f}
        };
        renderer.fillPolygon(innerTriangle, sf::Color(44, 160, 44));
    }
};