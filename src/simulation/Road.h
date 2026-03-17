#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"
#include <vector>

struct Road {
    Vec3 start;
    Vec3 end;
    float width;

    Road(Vec3 start, Vec3 end, float width = 1.0f)
        : start(start), end(end), width(width) {}

    void draw(Renderer& renderer) {
        Vec3 dir  = (end - start).normalize();
        Vec3 perp = {-dir.z, 0, dir.x};

        Vec3 p1 = start + perp * width;
        Vec3 p2 = start - perp * width;
        Vec3 p3 = end   - perp * width;
        Vec3 p4 = end   + perp * width;

        Vec2 s1 = renderer.project(p1);
        Vec2 s2 = renderer.project(p2);
        Vec2 s3 = renderer.project(p3);
        Vec2 s4 = renderer.project(p4);

        // main road surface
        std::vector<sf::Vector2f> surface = {
            {s1.x, s1.y}, {s2.x, s2.y},
            {s3.x, s3.y}, {s4.x, s4.y}
        };
        renderer.fillPolygon(surface, sf::Color(60, 60, 60));

        // road edges
        renderer.drawLine(s1, s4, sf::Color(200, 200, 200));
        renderer.drawLine(s2, s3, sf::Color(200, 200, 200));

        // dashed center line
        int dashCount = 6;
        for (int i = 0; i < dashCount; i++) {
            float t1 = (float)i / dashCount;
            float t2 = t1 + 0.04f;

            Vec3 d1 = {
                start.x + t1 * (end.x - start.x),
                0,
                start.z + t1 * (end.z - start.z)
            };
            Vec3 d2 = {
                start.x + t2 * (end.x - start.x),
                0,
                start.z + t2 * (end.z - start.z)
            };

            Vec2 ds1 = renderer.project(d1);
            Vec2 ds2 = renderer.project(d2);
            renderer.drawLine(ds1, ds2, sf::Color(255, 220, 0));
        }
    }
};