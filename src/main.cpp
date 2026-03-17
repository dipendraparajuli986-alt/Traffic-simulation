#include <SFML/Graphics.hpp>
#include "core/Renderer.h"
#include "math/Vec3.h"
#include "simulation/Road.h"
#include "simulation/Background.h"
#include "simulation/TrafficLight.h"
#include "simulation/ZebraCrossing.h"
#include "simulation/Car.h"
#include "simulation/Pedestrian.h"
#include "simulation/RoadsideProps.h"
#include "simulation/HUD.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1200, 700}), "Highway Simulation");
    Renderer renderer(window);

    Road highway({0, 0, 2}, {0, 0, 12}, 1.5f);
    Background background;
    TrafficLight light({2, 0, 6}, 4.0f);
    ZebraCrossing zebra({0, 0, 7}, 3.0f, 8);
    RoadsideProps props;
    HUD hud;

    Car car1({-0.4f, 0, 11}, 3.0f, 7.5f, sf::Color(140, 120, 100));
    Car car2({ 0.4f, 0, 10}, 2.5f, 7.5f, sf::Color(100, 110, 130));

    Pedestrian ped1({-1.8f, 0, 7}, { 1.8f, 0, 7}, 0.12f, sf::Color(220, 50,  50),  sf::Color(50,  50,  120));
    Pedestrian ped2({ 1.8f, 0, 7}, {-1.8f, 0, 7}, 0.10f, sf::Color(50,  150, 220), sf::Color(30,  30,  30));
    Pedestrian ped3({-1.8f, 0, 7}, { 1.8f, 0, 7}, 0.08f, sf::Color(50,  200, 50),  sf::Color(80,  40,  10));

    ped2.t = 0.5f;
    ped3.t = 0.25f;

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape) window.close();
                if (key->code == sf::Keyboard::Key::Num1) light.state = LightState::GREEN;
                if (key->code == sf::Keyboard::Key::Num2) light.state = LightState::RED;
                if (key->code == sf::Keyboard::Key::Num3) light.state = LightState::YELLOW;

                // reset camera
                if (key->code == sf::Keyboard::Key::R) {
                    renderer.camera.position = {0, -3, -1};
                    renderer.camera.pitch    = 0.35f;
                    renderer.camera.yaw      = 0.0f;
                }
            }

            // scroll wheel zoom
            if (auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                renderer.camera.position.z += scroll->delta * 0.5f;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            renderer.camera.position.z += 4.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            renderer.camera.position.z -= 4.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            renderer.camera.position.x -= 4.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            renderer.camera.position.x += 4.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            renderer.camera.position.y -= 4.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            renderer.camera.position.y += 4.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            renderer.camera.pitch -= 1.0f * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            renderer.camera.pitch += 1.0f * dt;

        light.update(dt);
        car1.update(dt, light);
        car2.update(dt, light);
        ped1.update(dt, light);
        ped2.update(dt, light);
        ped3.update(dt, light);

        renderer.clear(sf::Color(35, 35, 35));
        background.draw(window, renderer, 1200, 700);
        highway.draw(renderer);
        props.draw(renderer);
        zebra.draw(renderer);
        light.draw(renderer);
        car1.draw(renderer);
        car2.draw(renderer);
        ped1.draw(renderer);
        ped2.draw(renderer);
        ped3.draw(renderer);
        hud.draw(window, light);
        renderer.display();
    }

    return 0;
}