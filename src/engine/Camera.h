#pragma once
#include "../math/Vec3.h"
#include "../math/Matrix4.h"

struct Camera {
    Vec3 position;
    float pitch;
    float yaw;

    Camera(Vec3 position = {0, -8, -5}, float pitch = 0.8f, float yaw = 0.0f)
        : position(position), pitch(pitch), yaw(yaw) {}

    Vec3 apply(const Vec3& worldPoint) const {
        Vec3 translated = worldPoint - position;

        Matrix4 rotY = Matrix4::rotationY(yaw);
        Matrix4 rotX = Matrix4::rotationX(pitch);

        Vec3 result = rotY.transform(translated);
        result = rotX.transform(result);

        return result;
    }
};