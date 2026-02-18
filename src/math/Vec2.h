#pragma once
#include <cmath>

struct Vec2 {
    float x, y;

    Vec2(float x = 0, float y = 0) : x(x), y(y) {}

    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2 operator*(float t)       const { return {x * t, y * t}; }

    float length() const { return std::sqrt(x * x + y * y); }

    Vec2 normalize() const {
        float len = length();
        if (len == 0) return {0, 0};
        return {x / len, y / len};
    }
};