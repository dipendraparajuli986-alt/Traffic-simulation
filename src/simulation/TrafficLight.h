#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"

enum class LightState { RED, YELLOW, GREEN };

struct TrafficLight {
    Vec3 position;
    LightState state;
    float timer;
    float greenTime;
    float yellowTime;
    float redTime;
    float pedWalkTime;
    bool pedCanWalk;

    TrafficLight(Vec3 position, float greenTime = 5.0f, float yellowTime = 2.0f, float redTime = 6.0f)
        : position(position), state(LightState::GREEN),
          timer(0), greenTime(greenTime), yellowTime(yellowTime),
          redTime(redTime), pedWalkTime(0), pedCanWalk(false) {}

    void update(float dt) {
        timer += dt;

        if (state == LightState::GREEN) {
            pedCanWalk = false;
            if (timer >= greenTime) {
                timer = 0;
                state = LightState::YELLOW;
            }
        }
        else if (state == LightState::YELLOW) {
            pedCanWalk = false;
            if (timer >= yellowTime) {
                timer = 0;
                pedWalkTime = 0;
                state = LightState::RED;
            }
        }
        else if (state == LightState::RED) {
            // pedestrians chai red light ko 75% part ma hinxan
            pedWalkTime += dt;
            if (pedWalkTime < redTime * 0.75f)
                pedCanWalk = true;
            else
                pedCanWalk = false;

            if (timer >= redTime) {
                timer = 0;
                state = LightState::GREEN;
            }
        }
    }

    bool isRed()   { return state == LightState::RED;    }
    bool isGreen() { return state == LightState::GREEN;  }

    void draw(Renderer& renderer) {
        Vec2 poleBase = renderer.project({position.x, position.y + 0.1f,  position.z});
        Vec2 poleMid  = renderer.project({position.x, position.y - 1.0f,  position.z});
        Vec2 poleTop  = renderer.project({position.x, position.y - 2.0f,  position.z});

        for (int i = -2; i <= 2; i++) {
            renderer.drawLine(
                {poleBase.x + i, poleBase.y},
                {poleMid.x  + i, poleMid.y},
                sf::Color(100, 100, 100)
            );
        }
        for (int i = -1; i <= 1; i++) {
            renderer.drawLine(
                {poleMid.x + i, poleMid.y},
                {poleTop.x + i, poleTop.y},
                sf::Color(120, 120, 120)
            );
        }

        Vec3 hbl = {position.x - 0.15f, position.y - 1.1f, position.z};
        Vec3 hbr = {position.x + 0.15f, position.y - 1.1f, position.z};
        Vec3 htl = {position.x - 0.15f, position.y - 2.0f, position.z};
        Vec3 htr = {position.x + 0.15f, position.y - 2.0f, position.z};

        Vec2 shbl = renderer.project(hbl);
        Vec2 shbr = renderer.project(hbr);
        Vec2 shtl = renderer.project(htl);
        Vec2 shtr = renderer.project(htr);

        std::vector<sf::Vector2f> housing = {
            {shtl.x, shtl.y}, {shtr.x, shtr.y},
            {shbr.x, shbr.y}, {shbl.x, shbl.y}
        };
        renderer.fillPolygon(housing, sf::Color(40, 40, 40));
        renderer.drawLine(shtl, shtr, sf::Color(70, 70, 70));
        renderer.drawLine(shtr, shbr, sf::Color(70, 70, 70));
        renderer.drawLine(shbr, shbl, sf::Color(70, 70, 70));
        renderer.drawLine(shbl, shtl, sf::Color(70, 70, 70));

        Vec2 redPos    = renderer.project({position.x, position.y - 1.85f, position.z});
        Vec2 yellowPos = renderer.project({position.x, position.y - 1.55f, position.z});
        Vec2 greenPos  = renderer.project({position.x, position.y - 1.25f, position.z});

        sf::Color red    = sf::Color(60,  0,   0);
        sf::Color yellow = sf::Color(60,  60,  0);
        sf::Color green  = sf::Color(0,   60,  0);

        if (state == LightState::RED)    red    = sf::Color(255, 50,  50);
        if (state == LightState::YELLOW) yellow = sf::Color(255, 220, 0);
        if (state == LightState::GREEN)  green  = sf::Color(50,  255, 50);

        for (int r = 7; r >= 0; r--) {
            renderer.drawCircle(redPos.x,    redPos.y,    r, red);
            renderer.drawCircle(yellowPos.x, yellowPos.y, r, yellow);
            renderer.drawCircle(greenPos.x,  greenPos.y,  r, green);
        }

        if (state == LightState::RED) {
            renderer.drawCircle(redPos.x, redPos.y, 10, sf::Color(255, 50, 50, 60));
            renderer.drawCircle(redPos.x, redPos.y, 13, sf::Color(255, 50, 50, 30));
        }
        if (state == LightState::GREEN) {
            renderer.drawCircle(greenPos.x, greenPos.y, 10, sf::Color(50, 255, 50, 60));
            renderer.drawCircle(greenPos.x, greenPos.y, 13, sf::Color(50, 255, 50, 30));
        }
    }
};