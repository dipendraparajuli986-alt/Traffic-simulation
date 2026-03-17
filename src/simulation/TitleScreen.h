#pragma once
#include <SFML/Graphics.hpp>

struct TitleScreen {
    sf::Font font;
    bool fontLoaded;
    bool done;

    TitleScreen() : done(false) {
fontLoaded = font.openFromFile("/usr/share/fonts/TTF/FiraMono-Bold.ttf");    }

    bool isDone() { return done; }

    void handleEvent(sf::Event& event) {
        if (event.is<sf::Event::KeyPressed>())   done = true;
        if (event.is<sf::Event::MouseButtonPressed>()) done = true;
    }

    void draw(sf::RenderWindow& window) {
        // dark background
        sf::RectangleShape bg(sf::Vector2f(1200, 700));
        bg.setFillColor(sf::Color(15, 15, 25));
        window.draw(bg);

        // road lines for decoration
        for (int i = 0; i < 8; i++) {
            sf::RectangleShape line(sf::Vector2f(1200, 2));
            line.setPosition(sf::Vector2f(0, 100 + i * 80));
            line.setFillColor(sf::Color(30, 30, 50));
            window.draw(line);
        }

        if (!fontLoaded) return;

        auto makeText = [&](std::string str, float x, float y, int size, sf::Color color, bool center = false) {
            sf::Text text(font, str, size);
            if (center) {
                sf::FloatRect bounds = text.getLocalBounds();
                text.setPosition(sf::Vector2f(600 - bounds.size.x / 2, y));
            } else {
                text.setPosition(sf::Vector2f(x, y));
            }
            text.setFillColor(color);
            window.draw(text);
        };

        // title
        makeText("3D TRAFFIC SIMULATION", 0, 150, 48, sf::Color(255, 255, 255), true);

        // subtitle
        makeText("Computer Graphics & Visualization Project", 0, 220, 22, sf::Color(180, 180, 180), true);

        // divider line
        sf::RectangleShape divider(sf::Vector2f(600, 2));
        divider.setPosition(sf::Vector2f(300, 270));
        divider.setFillColor(sf::Color(100, 100, 200));
        window.draw(divider);

        // algorithms used
        makeText("Algorithms Used:", 0, 295, 18, sf::Color(150, 200, 255), true);
        makeText("DDA Line   |   Bresenham Line   |   Midpoint Circle", 0, 325, 16, sf::Color(200, 200, 200), true);
        makeText("Scanline Fill   |   Bezier Curve   |   3D Projection", 0, 350, 16, sf::Color(200, 200, 200), true);
        makeText("Matrix Transformations   |   Translation   |   Rotation   |   Scaling", 0, 375, 16, sf::Color(200, 200, 200), true);

        // divider
        sf::RectangleShape divider2(sf::Vector2f(600, 2));
        divider2.setPosition(sf::Vector2f(300, 410));
        divider2.setFillColor(sf::Color(100, 100, 200));
        window.draw(divider2);

        // controls
        makeText("Controls:", 0, 430, 18, sf::Color(150, 200, 255), true);
        makeText("1 - Green Light     2 - Red Light     3 - Yellow Light", 0, 458, 16, sf::Color(200, 200, 200), true);
        makeText("WASD - Move Camera     Q/E - Up/Down     Up/Down - Tilt", 0, 483, 16, sf::Color(200, 200, 200), true);
        makeText("Scroll / Z X - Zoom     R - Reset Camera", 0, 508, 16, sf::Color(200, 200, 200), true);

        // press any key
        makeText("Press any key to start...", 0, 600, 20, sf::Color(255, 220, 50), true);
    }
};