#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"

struct ZebraCrossing {
    Vec3 position;
    float width;
    int stripeCount;

    ZebraCrossing(Vec3 position, float width = 1.5f, int stripeCount = 6)
        : position(position), width(width), stripeCount(stripeCount) {}

    void draw(Renderer& renderer) {
        float stripeWidth = width / stripeCount;

        for (int i = 0; i < stripeCount; i++) {
            if (i % 2 == 0) continue;

            float xStart = position.x - width / 2 + i * stripeWidth;
            float xEnd   = xStart + stripeWidth;

            Vec3 p1 = {xStart, 0, position.z - 0.15f};
            Vec3 p2 = {xEnd,   0, position.z - 0.15f};
            Vec3 p3 = {xEnd,   0, position.z + 0.15f};
            Vec3 p4 = {xStart, 0, position.z + 0.15f};

            Vec2 s1 = renderer.project(p1);
            Vec2 s2 = renderer.project(p2);
            Vec2 s3 = renderer.project(p3);
            Vec2 s4 = renderer.project(p4);

            std::vector<sf::Vector2f> stripe = {
                {s1.x, s1.y}, {s2.x, s2.y},
                {s3.x, s3.y}, {s4.x, s4.y}
            };
            renderer.fillPolygon(stripe, sf::Color(220, 220, 220));
        }
    }
};