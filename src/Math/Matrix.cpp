#include "Matrix.h"
#include <cmath>
#include <cstdio>

Matrix4x4::Matrix4x4() {
    for (int i = 0; i < 16; ++i) {
        m[i] = 0.0f;
    }
}

Matrix4x4::Matrix4x4(const float data[16]) {
    for (int i = 0; i < 16; ++i) {
        m[i] = data[i];
    }
}

Matrix4x4::Matrix4x4(const Matrix4x4& other) {
    for (int i = 0; i < 16; ++i) {
        m[i] = other.m[i];
    }
}

// Macierz jednostkowa
Matrix4x4 Matrix4x4::Identity() {
    Matrix4x4 result;
    result.m[0] = 1.0f; result.m[4] = 0.0f; result.m[8] = 0.0f; result.m[12] = 0.0f;
    result.m[1] = 0.0f; result.m[5] = 1.0f; result.m[9] = 0.0f; result.m[13] = 0.0f;
    result.m[2] = 0.0f; result.m[6] = 0.0f; result.m[10] = 1.0f; result.m[14] = 0.0f;
    result.m[3] = 0.0f; result.m[7] = 0.0f; result.m[11] = 0.0f; result.m[15] = 1.0f;
    return result;
}

// Translacja
Matrix4x4 Matrix4x4::Translation(float x, float y, float z) {
    Matrix4x4 result = Identity();
    result.m[12] = x;
    result.m[13] = y;
    result.m[14] = z;
    return result;
}

Matrix4x4 Matrix4x4::Translation(const ImVec3& translation) {
    return Translation(translation.x, translation.y, translation.z);
}

// Rotacja wokó³ osi X
Matrix4x4 Matrix4x4::RotationX(float angleDegrees) {
    float angleRad = angleDegrees * M_PI / 180.0f;// poprawka
    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);

    Matrix4x4 result = Identity();
    result.m[5] = cosA;
    result.m[6] = sinA;
    result.m[9] = -sinA;
    result.m[10] = cosA;
    return result;
}

// Rotacja wokó³ osi Y
Matrix4x4 Matrix4x4::RotationY(float angleDegrees) {
    float angleRad = angleDegrees * M_PI / 180.0f;
    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);

    Matrix4x4 result = Identity();
    result.m[0] = cosA;
    result.m[2] = -sinA;
    result.m[8] = sinA;
    result.m[10] = cosA;
    return result;
}

// Rotacja wokó³ osi Z
Matrix4x4 Matrix4x4::RotationZ(float angleDegrees) {
    float angleRad = angleDegrees * M_PI / 180.0f;
    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);

    Matrix4x4 result = Identity();
    result.m[0] = cosA;
    result.m[1] = sinA;
    result.m[4] = -sinA;
    result.m[5] = cosA;
    return result;
}

// Rotacja Eulera (kolejnoœæ: Z, Y, X)
Matrix4x4 Matrix4x4::RotationEuler(float rx, float ry, float rz) {
    Matrix4x4 rotZ = RotationZ(rz);
    Matrix4x4 rotY = RotationY(ry);
    Matrix4x4 rotX = RotationX(rx);

    // Z * Y * X (kolejnoœæ aplikowania transformacji)
    return rotZ.Multiply(rotY).Multiply(rotX);
}

// Skalowanie
Matrix4x4 Matrix4x4::Scale(float sx, float sy, float sz) {
    Matrix4x4 result = Identity();
    result.m[0] = sx;
    result.m[5] = sy;
    result.m[10] = sz;
    return result;
}

Matrix4x4 Matrix4x4::Scale(const ImVec3& scale) {
    return Scale(scale.x, scale.y, scale.z);
}

// Mno¿enie macierzy
Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& other) const {
    Matrix4x4 result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }

    return result;
}

// Transformacja punktu (z dodaniem w=1)
ImVec3 Matrix4x4::TransformPoint(const ImVec3& point) const {
    float x = point.x * m[0] + point.y * m[4] + point.z * m[8] + m[12];
    float y = point.x * m[1] + point.y * m[5] + point.z * m[9] + m[13];
    float z = point.x * m[2] + point.y * m[6] + point.z * m[10] + m[14];
    float w = point.x * m[3] + point.y * m[7] + point.z * m[11] + m[15];

    // Perspektywa (jeœli w != 1)
    if (w != 0.0f && w != 1.0f) {
        x /= w;
        y /= w;
        z /= w;
    }

    return ImVec3(x, y, z);
}

// Transformacja wektora (bez translacji, w=0)
ImVec3 Matrix4x4::TransformVector(const ImVec3& vector) const {
    float x = vector.x * m[0] + vector.y * m[4] + vector.z * m[8];
    float y = vector.x * m[1] + vector.y * m[5] + vector.z * m[9];
    float z = vector.x * m[2] + vector.y * m[6] + vector.z * m[10];

    return ImVec3(x, y, z);
}

// Operatory
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    return Multiply(other);
}

ImVec3 Matrix4x4::operator*(const ImVec3& point) const {
    return TransformPoint(point);
}

// Dostêp do elementów
float& Matrix4x4::operator()(int row, int col) {
    return m[col * 4 + row]; // column-major order
}

float Matrix4x4::operator()(int row, int col) const {
    return m[col * 4 + row];
}

// Transpozycja
Matrix4x4 Matrix4x4::Transpose() const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(i, j) = (*this)(j, i);
        }
    }
    return result;
}

// Debugowanie
void Matrix4x4::Print() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::printf("%8.3f ", (*this)(i, j));
        }
        std::printf("\n");
    }
}