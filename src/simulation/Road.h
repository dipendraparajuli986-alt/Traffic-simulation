#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"
#include <vector>

struct Road {
    Vec3 start;
    Vec3 end;
    float width;

    Road(Vec3 start, Vec3 end, float width = 1.5f)
        : start(start), end(end), width(width) {}

    void draw(Renderer& renderer) {
        Vec3 dir  = (end - start).normalize();
        Vec3 perp = {-dir.z, 0, dir.x};

        int segments = 8;

        for (int i = 0; i < segments; i++) {
            float t1 = (float)i       / segments;
            float t2 = (float)(i + 1) / segments;

            Vec3 segStart = {
                start.x + t1 * (end.x - start.x),
                0,
                start.z + t1 * (end.z - start.z)
            };
            Vec3 segEnd = {
                start.x + t2 * (end.x - start.x),
                0,
                start.z + t2 * (end.z - start.z)
            };

            Vec3 p1 = segStart + perp * width;
            Vec3 p2 = segStart - perp * width;
            Vec3 p3 = segEnd   - perp * width;
            Vec3 p4 = segEnd   + perp * width;

            Vec3 cp1 = renderer.camera.apply(p1);
            Vec3 cp2 = renderer.camera.apply(p2);
            Vec3 cp3 = renderer.camera.apply(p3);
            Vec3 cp4 = renderer.camera.apply(p4);

if (cp1.z <= 0 && cp2.z <= 0 && cp3.z <= 0 && cp4.z <= 0) continue;
            Vec2 s1 = renderer.project(p1);
            Vec2 s2 = renderer.project(p2);
            Vec2 s3 = renderer.project(p3);
            Vec2 s4 = renderer.project(p4);

            std::vector<sf::Vector2f> surface = {
                {s1.x, s1.y}, {s2.x, s2.y},
                {s3.x, s3.y}, {s4.x, s4.y}
            };

            renderer.fillPolygon(surface, sf::Color(60, 60, 60));
            renderer.drawLine(s1, s4, sf::Color(200, 200, 200));
            renderer.drawLine(s2, s3, sf::Color(200, 200, 200));
        }

        int dashCount = 20;
        for (int i = 0; i < dashCount; i++) {
            float t1 = (float)i / dashCount;
            float t2 = t1 + 0.025f;

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

            Vec3 cd1 = renderer.camera.apply(d1);
Vec3 cd2 = renderer.camera.apply(d2);

if (cd1.z <= 0 && cd2.z <= 0) continue;
            Vec2 ds1 = renderer.project(d1);
            Vec2 ds2 = renderer.project(d2);
            renderer.drawLine(ds1, ds2, sf::Color(255, 220, 0));
        }
    }
};