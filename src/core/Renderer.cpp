#include "Renderer.h"
#include "../math/Matrix4.h"

Renderer::Renderer(sf::RenderWindow& window)
    : m_window(window), m_proj(300.0f, 1200.0f, 700.0f),
      camera({0, -8, -5}, 0.8f, 0.0f) {}

void Renderer::clear(sf::Color color) {
    m_window.clear(color);
}

void Renderer::display() {
    m_window.display();
}

void Renderer::drawLine(Vec2 p1, Vec2 p2, sf::Color color) {
    Bresenham::drawLine(m_window, p1.x, p1.y, p2.x, p2.y, color);
}

void Renderer::drawCircle(int cx, int cy, int radius, sf::Color color) {
    MidpointCircle::drawCircle(m_window, cx, cy, radius, color);
}

void Renderer::fillPolygon(std::vector<sf::Vector2f> points, sf::Color color) {
    ScanlineFill::fillPolygon(m_window, points, color);
}

Vec2 Renderer::project(const Vec3& point) {
    Vec3 cameraSpace = camera.apply(point);
    return m_proj.project(cameraSpace);
}