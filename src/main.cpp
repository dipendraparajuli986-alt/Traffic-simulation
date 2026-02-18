#include <SFML/Graphics.hpp>
#include "core/Renderer.h"
#include "math/Vec3.h"
#include "simulation/Road.h"
#include "simulation/TrafficLight.h"
#include "simulation/Car.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1200, 700}), "Traffic Sim");
    Renderer renderer(window);

    Road road1({-8, 0, 2}, {8, 0, 12}, 1.0f);
    Road road2({-8, 0, 6}, {8, 0, 16}, 1.0f);

    TrafficLight light1({0, 0, 6},  3.0f);
    TrafficLight light2({0, 0, 10}, 3.0f);
    light2.state = LightState::RED;

    Car car1({-8, 0, 2},  {8, 0, 12}, 0.06f, sf::Color(220, 50,  50));
    Car car2({-8, 0, 2},  {8, 0, 12}, 0.04f, sf::Color(50,  50,  220));
    Car car3({-8, 0, 6},  {8, 0, 16}, 0.07f, sf::Color(50,  200, 50));
    Car car4({-8, 0, 6},  {8, 0, 16}, 0.05f, sf::Color(220, 180, 0));

    car2.t = 0.3f;
    car4.t = 0.5f;

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (auto* key = event->getIf<sf::Event::KeyPressed>())
                if (key->code == sf::Keyboard::Key::Escape)
                    window.close();
        }

        // camera controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            renderer.camera.position.z += 3.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            renderer.camera.position.z -= 3.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            renderer.camera.position.x -= 3.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            renderer.camera.position.x += 3.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            renderer.camera.position.y -= 3.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            renderer.camera.position.y += 3.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            renderer.camera.pitch -= 1.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            renderer.camera.pitch += 1.0f * dt;

        light1.update(dt);
        light2.update(dt);
        car1.update(dt, light1);
        car2.update(dt, light1);
        car3.update(dt, light2);
        car4.update(dt, light2);

        renderer.clear();
        road1.draw(renderer);
        road2.draw(renderer);
        light1.draw(renderer);
        light2.draw(renderer);
        car1.draw(renderer);
        car2.draw(renderer);
        car3.draw(renderer);
        car4.draw(renderer);
        renderer.display();
    }

    return 0;
}