#pragma once
#include <SFML/Graphics.hpp>
#include "TrafficLight.h"

struct HUD {
    sf::Font font;
    bool fontLoaded;

    HUD() {
fontLoaded = font.openFromFile("/usr/share/fonts/TTF/FiraMono-Bold.ttf");    }

    void draw(sf::RenderWindow& window, TrafficLight& light) {
        // background panel
        sf::RectangleShape panel(sf::Vector2f(220, 195));
        panel.setPosition(sf::Vector2f(10, 10));
        panel.setFillColor(sf::Color(0, 0, 0, 160));
        window.draw(panel);

        // traffic light state indicator
        sf::CircleShape indicator(15);
        indicator.setPosition(sf::Vector2f(20, 20));

        if      (light.state == LightState::RED)    indicator.setFillColor(sf::Color(255, 50,  50));
        else if (light.state == LightState::YELLOW) indicator.setFillColor(sf::Color(255, 220, 0));
        else                                         indicator.setFillColor(sf::Color(50,  255, 50));

        window.draw(indicator);

        if (!fontLoaded) return;

        auto makeText = [&](std::string str, float x, float y, int size, sf::Color color) {
            sf::Text text(font, str, size);
            text.setPosition(sf::Vector2f(x, y));
            text.setFillColor(color);
            window.draw(text);
        };

        std::string stateStr =
            light.state == LightState::RED    ? "RED   - Cars Stop" :
            light.state == LightState::YELLOW ? "YELLOW - Slow Down" :
                                                "GREEN  - Cars Go";

        makeText(stateStr,         60,  25, 14, sf::Color::White);
        makeText("CONTROLS:",      20,  70, 13, sf::Color(200, 200, 200));
        makeText("1 - Green",      20,  90, 12, sf::Color(50,  255, 50));
        makeText("2 - Red",        20, 108, 12, sf::Color(255, 50,  50));
        makeText("3 - Yellow",     20, 126, 12, sf::Color(255, 220, 0));
makeText("WASD - Camera",   20, 144, 12, sf::Color(180, 180, 180));
makeText("Scroll - Zoom",   20, 160, 12, sf::Color(180, 180, 180));
makeText("R - Reset View",  20, 176, 12, sf::Color(180, 180, 180));    }
};