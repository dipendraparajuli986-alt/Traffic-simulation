#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"
#include "TrafficLight.h"

struct Car {
    Vec3 position;
    float speed;
    float stopZ;
    sf::Color color;
    bool active;

    Car(Vec3 startPos, float speed, float stopZ, sf::Color color)
        : position(startPos), speed(speed), stopZ(stopZ), color(color), active(true) {}

    void update(float dt, TrafficLight& light) {
        if (!active) return;

        if (light.isRed() && position.z <= stopZ + 0.1f) return;

        position.z -= speed * dt;

        if (position.z < 1.0f) {
            position.z = 12.0f;
        }
    }

    void draw(Renderer& renderer) {
        if (!active) return;

        Vec3 dir  = {0, 0, -1};
        Vec3 perp = {1, 0,  0};
        Vec3 up   = {0, -1, 0};

        float hw = 0.25f;
        float hl = 0.4f;
        float hh = 0.25f;

        Vec3 b1 = position + perp * hw  + dir * hl;
        Vec3 b2 = position - perp * hw  + dir * hl;
        Vec3 b3 = position - perp * hw  - dir * hl;
        Vec3 b4 = position + perp * hw  - dir * hl;

        Vec3 t1 = b1 + up * hh;
        Vec3 t2 = b2 + up * hh;
        Vec3 t3 = b3 + up * hh;
        Vec3 t4 = b4 + up * hh;

        float rs = 0.1f;
        Vec3 r1 = position + perp * (hw - rs) + dir * (hl - rs) + up * (hh + 0.12f);
        Vec3 r2 = position - perp * (hw - rs) + dir * (hl - rs) + up * (hh + 0.12f);
        Vec3 r3 = position - perp * (hw - rs) - dir * (hl - rs) + up * (hh + 0.12f);
        Vec3 r4 = position + perp * (hw - rs) - dir * (hl - rs) + up * (hh + 0.12f);

        Vec2 pb1 = renderer.project(b1);
        Vec2 pb2 = renderer.project(b2);
        Vec2 pb3 = renderer.project(b3);
        Vec2 pb4 = renderer.project(b4);
        Vec2 pt1 = renderer.project(t1);
        Vec2 pt2 = renderer.project(t2);
        Vec2 pt3 = renderer.project(t3);
        Vec2 pt4 = renderer.project(t4);
        Vec2 pr1 = renderer.project(r1);
        Vec2 pr2 = renderer.project(r2);
        Vec2 pr3 = renderer.project(r3);
        Vec2 pr4 = renderer.project(r4);

        sf::Color sideColor = sf::Color(color.r * 0.7f, color.g * 0.7f, color.b * 0.7f);
        sf::Color roofColor = sf::Color(color.r * 0.9f, color.g * 0.9f, color.b * 0.9f);

        std::vector<sf::Vector2f> bottom = {{pb1.x,pb1.y},{pb2.x,pb2.y},{pb3.x,pb3.y},{pb4.x,pb4.y}};
        renderer.fillPolygon(bottom, sideColor);

        std::vector<sf::Vector2f> front = {{pb1.x,pb1.y},{pb2.x,pb2.y},{pt2.x,pt2.y},{pt1.x,pt1.y}};
        renderer.fillPolygon(front, sideColor);

        std::vector<sf::Vector2f> back = {{pb3.x,pb3.y},{pb4.x,pb4.y},{pt4.x,pt4.y},{pt3.x,pt3.y}};
        renderer.fillPolygon(back, sideColor);

        std::vector<sf::Vector2f> left = {{pb1.x,pb1.y},{pb4.x,pb4.y},{pt4.x,pt4.y},{pt1.x,pt1.y}};
        renderer.fillPolygon(left, color);

        std::vector<sf::Vector2f> right = {{pb2.x,pb2.y},{pb3.x,pb3.y},{pt3.x,pt3.y},{pt2.x,pt2.y}};
        renderer.fillPolygon(right, color);

        std::vector<sf::Vector2f> top = {{pt1.x,pt1.y},{pt2.x,pt2.y},{pt3.x,pt3.y},{pt4.x,pt4.y}};
        renderer.fillPolygon(top, color);

        std::vector<sf::Vector2f> roof = {{pr1.x,pr1.y},{pr2.x,pr2.y},{pr3.x,pr3.y},{pr4.x,pr4.y}};
        renderer.fillPolygon(roof, roofColor);

        std::vector<sf::Vector2f> windshield = {{pt1.x,pt1.y},{pt2.x,pt2.y},{pr2.x,pr2.y},{pr1.x,pr1.y}};
        renderer.fillPolygon(windshield, sf::Color(150, 220, 255, 180));

        std::vector<sf::Vector2f> rearWindow = {{pt3.x,pt3.y},{pt4.x,pt4.y},{pr4.x,pr4.y},{pr3.x,pr3.y}};
        renderer.fillPolygon(rearWindow, sf::Color(150, 220, 255, 180));

        renderer.drawLine(pb1, pb2, sf::Color::Black);
        renderer.drawLine(pb2, pb3, sf::Color::Black);
        renderer.drawLine(pb3, pb4, sf::Color::Black);
        renderer.drawLine(pb4, pb1, sf::Color::Black);
        renderer.drawLine(pt1, pt2, sf::Color::Black);
        renderer.drawLine(pt2, pt3, sf::Color::Black);
        renderer.drawLine(pt3, pt4, sf::Color::Black);
        renderer.drawLine(pt4, pt1, sf::Color::Black);
        renderer.drawLine(pb1, pt1, sf::Color::Black);
        renderer.drawLine(pb2, pt2, sf::Color::Black);
        renderer.drawLine(pb3, pt3, sf::Color::Black);
        renderer.drawLine(pb4, pt4, sf::Color::Black);

        Vec2 wfl = renderer.project(position + perp * hw * 1.1f + dir * hl * 0.6f);
        Vec2 wfr = renderer.project(position - perp * hw * 1.1f + dir * hl * 0.6f);
        Vec2 wbl = renderer.project(position + perp * hw * 1.1f - dir * hl * 0.6f);
        Vec2 wbr = renderer.project(position - perp * hw * 1.1f - dir * hl * 0.6f);

        renderer.drawCircle(wfl.x, wfl.y, 5, sf::Color(30, 30, 30));
        renderer.drawCircle(wfr.x, wfr.y, 5, sf::Color(30, 30, 30));
        renderer.drawCircle(wbl.x, wbl.y, 5, sf::Color(30, 30, 30));
        renderer.drawCircle(wbr.x, wbr.y, 5, sf::Color(30, 30, 30));
    }
};