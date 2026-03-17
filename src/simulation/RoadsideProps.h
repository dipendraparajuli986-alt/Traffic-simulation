#pragma once
#include "../core/Renderer.h"
#include "../math/Vec3.h"
#include <cmath>
#include <vector>

struct RoadsideProps {

    void drawPole(Renderer& renderer, Vec3 position) {
        Vec2 base = renderer.project({position.x, position.y,        position.z});
        Vec2 top  = renderer.project({position.x, position.y - 2.0f, position.z});

        for (int i = -1; i <= 1; i++) {
            renderer.drawLine(
                {base.x + i, base.y},
                {top.x  + i, top.y},
                sf::Color(150, 150, 150)
            );
        }

        // light on top
        for (int r = 4; r >= 0; r--)
            renderer.drawCircle(top.x, top.y, r, sf::Color(255, 240, 180));

        renderer.drawCircle(top.x, top.y, 7, sf::Color(255, 240, 180, 40));
    }

    void drawTree(Renderer& renderer, Vec3 position) {
        Vec2 base = renderer.project({position.x, position.y,        position.z});
        Vec2 top  = renderer.project({position.x, position.y - 1.5f, position.z});

        // trunk
        for (int i = -2; i <= 2; i++) {
            renderer.drawLine(
                {base.x + i, base.y},
                {top.x  + i, top.y},
                sf::Color(100, 60, 20)
            );
        }

        // 3 layers of foliage
        Vec2 f1 = renderer.project({position.x, position.y - 1.5f, position.z});
        Vec2 f2 = renderer.project({position.x, position.y - 2.2f, position.z});
        Vec2 f3 = renderer.project({position.x, position.y - 2.8f, position.z});

        for (int r = 18; r >= 0; r--)
            renderer.drawCircle(f1.x, f1.y, r, sf::Color(30 + r, 100 + r, 30));
        for (int r = 15; r >= 0; r--)
            renderer.drawCircle(f2.x, f2.y, r, sf::Color(30 + r, 110 + r, 30));
        for (int r = 10; r >= 0; r--)
            renderer.drawCircle(f3.x, f3.y, r, sf::Color(40 + r, 120 + r, 40));
    }

    void draw(Renderer& renderer) {
        // left side trees
        drawTree(renderer, {-2.5f, 0, 3});
        drawTree(renderer, {-2.5f, 0, 5});
        drawTree(renderer, {-2.5f, 0, 7});
        drawTree(renderer, {-2.5f, 0, 9});
        drawTree(renderer, {-2.5f, 0, 11});

        // right side trees
        drawTree(renderer, {2.5f, 0, 3});
        drawTree(renderer, {2.5f, 0, 5});
        drawTree(renderer, {2.5f, 0, 9});
        drawTree(renderer, {2.5f, 0, 11});

        // poles on right side
        drawPole(renderer, {2.2f, 0, 4});
        drawPole(renderer, {2.2f, 0, 7});
        drawPole(renderer, {2.2f, 0, 10});
    }
};