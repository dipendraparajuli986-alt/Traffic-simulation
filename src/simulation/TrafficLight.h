#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"

enum class LightState { RED , YELLOW , GREEN };

struct TrafficLight {
    Vec3 position;
    LightState state;
    float timer;
    float switchTime;

    TrafficLight(Vec3 position, float switchTime = 3.0f)
    : position(position) , state(LightState::GREEN),timer(0), switchTime(switchTime) {}
    
    void update(float dt) {
        timer += dt;
        if (timer >= switchTime) {
            timer = 0;
            if      (state == LightState::GREEN)  state = LightState::YELLOW;
            else if (state == LightState::YELLOW) state = LightState::RED;
            else if (state == LightState::RED)    state = LightState::GREEN;
        }
    }

    bool isRed() { return state == LightState::RED; }

    void draw(Renderer& renderer) {
        Vec2 base = renderer.project(position);
        Vec2 top  = renderer.project({position.x, position.y - 1.5f, position.z});

        renderer.drawLine(base, top, sf::Color(150, 150, 150));

        Vec2 redPos    = renderer.project({position.x, position.y - 1.5f, position.z});
        Vec2 yellowPos = renderer.project({position.x, position.y - 1.2f, position.z});
        Vec2 greenPos  = renderer.project({position.x, position.y - 0.9f, position.z});

        sf::Color dimRed    = sf::Color(80, 0, 0);
        sf::Color dimYellow = sf::Color(80, 80, 0);
        sf::Color dimGreen  = sf::Color(0, 80, 0);

        if (state == LightState::RED)    dimRed    = sf::Color::Red;
        if (state == LightState::YELLOW) dimYellow = sf::Color::Yellow;
        if (state == LightState::GREEN)  dimGreen  = sf::Color::Green;

        renderer.drawCircle(redPos.x,    redPos.y,    8, dimRed);
        renderer.drawCircle(yellowPos.x, yellowPos.y, 8, dimYellow);
        renderer.drawCircle(greenPos.x,  greenPos.y,  8, dimGreen);
    }
};