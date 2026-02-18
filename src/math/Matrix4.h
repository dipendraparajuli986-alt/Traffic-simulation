#pragma once
#include "Vec3.h"
#include <cmath>

struct Matrix4 {
    float m[4][4];

    Matrix4() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = 0;
    }

    static Matrix4 identity() {
        Matrix4 mat;
        mat.m[0][0] = 1;
        mat.m[1][1] = 1;
        mat.m[2][2] = 1;
        mat.m[3][3] = 1;
        return mat;
    }

    static Matrix4 translation(float tx, float ty, float tz) {
        Matrix4 mat = identity();
        mat.m[0][3] = tx;
        mat.m[1][3] = ty;
        mat.m[2][3] = tz;
        return mat;
    }

    static Matrix4 scale(float sx, float sy, float sz) {
        Matrix4 mat = identity();
        mat.m[0][0] = sx;
        mat.m[1][1] = sy;
        mat.m[2][2] = sz;
        return mat;
    }

    static Matrix4 rotationX(float angle) {
        Matrix4 mat = identity();
        mat.m[1][1] =  std::cos(angle);
        mat.m[1][2] = -std::sin(angle);
        mat.m[2][1] =  std::sin(angle);
        mat.m[2][2] =  std::cos(angle);
        return mat;
    }

    static Matrix4 rotationY(float angle) {
        Matrix4 mat = identity();
        mat.m[0][0] =  std::cos(angle);
        mat.m[0][2] =  std::sin(angle);
        mat.m[2][0] = -std::sin(angle);
        mat.m[2][2] =  std::cos(angle);
        return mat;
    }

    static Matrix4 rotationZ(float angle) {
        Matrix4 mat = identity();
        mat.m[0][0] =  std::cos(angle);
        mat.m[0][1] = -std::sin(angle);
        mat.m[1][0] =  std::sin(angle);
        mat.m[1][1] =  std::cos(angle);
        return mat;
    }

    Matrix4 operator*(const Matrix4& o) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    result.m[i][j] += m[i][k] * o.m[k][j];
        return result;
    }

    Vec3 transform(const Vec3& v) const {
        float x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3];
        float y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3];
        float z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3];
        return {x, y, z};
    }
};