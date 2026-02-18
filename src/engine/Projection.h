#pragma once
#include "../math/Vec2.h"
#include "../math/Vec3.h"

struct Projection {
    float fov;
    float screenWidth;
    float screenHeight;

    Projection(float fov = 400.0f, float screenWidth = 800.0f, float screenHeight = 600.0f)
        : fov(fov), screenWidth(screenWidth), screenHeight(screenHeight) {}

    Vec2 project(const Vec3& point) const {
        float z = point.z + 5.0f;
        if (z == 0) z = 0.001f;
        float x = (point.x / z) * fov + screenWidth  / 2.0f;
        float y = (point.y / z) * fov + screenHeight / 2.0f;
        return {x, y};
    }
};