#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"
#include "TrafficLight.h"

struct Car {
    Vec3 position;
    Vec3 start;
    Vec3 end;
    float speed;
    float t;
    sf::Color color;

    Car(Vec3 start, Vec3 end, float speed, sf::Color color)
        : start(start), end(end), speed(speed), color(color), t(0)
    {
        position = start;
    }

    void update(float dt, TrafficLight& light) {
        Vec3 toLight = light.position - position;
        float distToLight = toLight.length();
        if (light.isRed() && distToLight < 0.8f) return;
        t += speed * dt;
        if (t > 1.0f) t = 0.0f;
        position.x = start.x + t * (end.x - start.x);
        position.y = start.y + t * (end.y - start.y);
        position.z = start.z + t * (end.z - start.z);
    }

    void draw(Renderer& renderer) {
        Vec3 dir  = (end - start).normalize();
        Vec3 perp = {-dir.z, 0, dir.x};

        float hw = 0.22f;
        float hl = 0.4f;

        // --- car body ---
        Vec3 p1 = position + perp * hw + dir * hl;
        Vec3 p2 = position - perp * hw + dir * hl;
        Vec3 p3 = position - perp * hw - dir * hl;
        Vec3 p4 = position + perp * hw - dir * hl;

        Vec2 s1 = renderer.project(p1);
        Vec2 s2 = renderer.project(p2);
        Vec2 s3 = renderer.project(p3);
        Vec2 s4 = renderer.project(p4);

        std::vector<sf::Vector2f> body = {
            {s1.x, s1.y}, {s2.x, s2.y},
            {s3.x, s3.y}, {s4.x, s4.y}
        };
        renderer.fillPolygon(body, color);
        renderer.drawLine(s1, s2, sf::Color::Black);
        renderer.drawLine(s2, s3, sf::Color::Black);
        renderer.drawLine(s3, s4, sf::Color::Black);
        renderer.drawLine(s4, s1, sf::Color::Black);

        // --- windshield (front, smaller rectangle) ---
        Vec3 w1 = position + perp * hw * 0.7f + dir * hl * 0.9f;
        Vec3 w2 = position - perp * hw * 0.7f + dir * hl * 0.9f;
        Vec3 w3 = position - perp * hw * 0.7f + dir * hl * 0.4f;
        Vec3 w4 = position + perp * hw * 0.7f + dir * hl * 0.4f;

        Vec2 ws1 = renderer.project(w1);
        Vec2 ws2 = renderer.project(w2);
        Vec2 ws3 = renderer.project(w3);
        Vec2 ws4 = renderer.project(w4);

        std::vector<sf::Vector2f> windshield = {
            {ws1.x, ws1.y}, {ws2.x, ws2.y},
            {ws3.x, ws3.y}, {ws4.x, ws4.y}
        };
        renderer.fillPolygon(windshield, sf::Color(150, 220, 255));
        renderer.drawLine(ws1, ws2, sf::Color::Black);
        renderer.drawLine(ws2, ws3, sf::Color::Black);
        renderer.drawLine(ws3, ws4, sf::Color::Black);
        renderer.drawLine(ws4, ws1, sf::Color::Black);

        // --- wheels (4 circles) ---
        float wr = 5;
        Vec2 wfl = renderer.project(position + perp * hw * 1.0f + dir * hl * 0.6f);
        Vec2 wfr = renderer.project(position - perp * hw * 1.0f + dir * hl * 0.6f);
        Vec2 wbl = renderer.project(position + perp * hw * 1.0f - dir * hl * 0.6f);
        Vec2 wbr = renderer.project(position - perp * hw * 1.0f - dir * hl * 0.6f);

        renderer.drawCircle(wfl.x, wfl.y, wr, sf::Color::Black);
        renderer.drawCircle(wfr.x, wfr.y, wr, sf::Color::Black);
        renderer.drawCircle(wbl.x, wbl.y, wr, sf::Color::Black);
        renderer.drawCircle(wbr.x, wbr.y, wr, sf::Color::Black);
    }
};