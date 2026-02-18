#pragma once
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    Vec3 operator*(float t)       const { return {x * t, y * t, z * t}; }

    float dot(const Vec3& o)   const { return x*o.x + y*o.y + z*o.z; }

    Vec3 cross(const Vec3& o) const {
        return {
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        };
    }

    float length() const { return std::sqrt(x*x + y*y + z*z); }

    Vec3 normalize() const {
        float len = length();
        if (len == 0) return {0, 0, 0};
        return {x/len, y/len, z/len};
    }
};