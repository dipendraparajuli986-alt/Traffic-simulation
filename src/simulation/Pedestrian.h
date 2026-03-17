#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"
#include "TrafficLight.h"
#include <cmath>

struct Pedestrian {
    Vec3 position;
    Vec3 start;
    Vec3 end;
    float speed;
    float t;
    sf::Color shirtColor;
    sf::Color pantsColor;

    Pedestrian(Vec3 start, Vec3 end, float speed, sf::Color shirtColor, sf::Color pantsColor)
        : start(start), end(end), speed(speed), shirtColor(shirtColor), pantsColor(pantsColor), t(0)
    {
        position = start;
    }

    void update(float dt, TrafficLight& light) {
        if (light.isGreen()) return;

        t += speed * dt;
        if (t > 1.0f) t = 0.0f;

        position.x = start.x + t * (end.x - start.x);
        position.y = start.y + t * (end.y - start.y);
        position.z = start.z + t * (end.z - start.z);
    }

    void draw(Renderer& renderer) {
        Vec2 pos = renderer.project(position);

        float legSwing = std::sin(t * 30.0f) * 5.0f;

        std::vector<sf::Vector2f> shadow = {
            {pos.x - 6, pos.y + 11},
            {pos.x + 6, pos.y + 11},
            {pos.x + 4, pos.y + 14},
            {pos.x - 4, pos.y + 14}
        };
        renderer.fillPolygon(shadow, sf::Color(0, 0, 0, 80));

        for (int r = 5; r >= 0; r--)
            renderer.drawCircle(pos.x, pos.y - 14, r, sf::Color(255, 210, 170));

        for (int r = 5; r >= 3; r--)
            renderer.drawCircle(pos.x, pos.y - 18, r, sf::Color(60, 30, 10));

        std::vector<sf::Vector2f> body = {
            {pos.x - 5, pos.y - 8},
            {pos.x + 5, pos.y - 8},
            {pos.x + 4, pos.y + 1},
            {pos.x - 4, pos.y + 1}
        };
        renderer.fillPolygon(body, shirtColor);

        renderer.drawLine({pos.x - 6, pos.y - 7}, {pos.x + 6, pos.y - 7}, shirtColor);

        renderer.drawLine(
            {pos.x - 5, pos.y - 6},
            {pos.x - 5 - legSwing * 0.4f, pos.y + 1},
            shirtColor
        );
        renderer.drawLine(
            {pos.x + 5, pos.y - 6},
            {pos.x + 5 + legSwing * 0.4f, pos.y + 1},
            shirtColor
        );

        std::vector<sf::Vector2f> pants = {
            {pos.x - 4, pos.y + 1},
            {pos.x + 4, pos.y + 1},
            {pos.x + 3, pos.y + 5},
            {pos.x - 3, pos.y + 5}
        };
        renderer.fillPolygon(pants, pantsColor);

        renderer.drawLine(
            {pos.x - 2, pos.y + 5},
            {pos.x - 2 + legSwing, pos.y + 11},
            pantsColor
        );
        renderer.drawLine(
            {pos.x + 2, pos.y + 5},
            {pos.x + 2 - legSwing, pos.y + 11},
            pantsColor
        );

        renderer.drawLine(
            {pos.x - 2 + legSwing,        pos.y + 11},
            {pos.x - 2 + legSwing - 3.0f, pos.y + 12},
            sf::Color(40, 20, 10)
        );
        renderer.drawLine(
            {pos.x + 2 - legSwing,        pos.y + 11},
            {pos.x + 2 - legSwing + 3.0f, pos.y + 12},
            sf::Color(40, 20, 10)
        );
    }
};