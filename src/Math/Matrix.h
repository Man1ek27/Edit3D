#pragma once

#include "PCH.h"

class Matrix4x4 {
public:
    // Konstruktory
    Matrix4x4();
    Matrix4x4(const float data[16]);
    Matrix4x4(const Matrix4x4& other);

    // Macierz jednostkowa
    static Matrix4x4 Identity();

    // Podstawowe transformacje
    static Matrix4x4 Translation(float x, float y, float z);
    static Matrix4x4 Translation(const ImVec3& translation);

    static Matrix4x4 RotationX(float angleDegrees);
    static Matrix4x4 RotationY(float angleDegrees);
    static Matrix4x4 RotationZ(float angleDegrees);
    static Matrix4x4 RotationEuler(float rx, float ry, float rz); // Kolejnoœæ: Z, Y, X

    static Matrix4x4 Scale(float sx, float sy, float sz);
    static Matrix4x4 Scale(const ImVec3& scale);

    // Operacje na macierzach
    Matrix4x4 Multiply(const Matrix4x4& other) const;
    ImVec3 TransformPoint(const ImVec3& point) const;
    ImVec3 TransformVector(const ImVec3& vector) const;

    // Operatory
    Matrix4x4 operator*(const Matrix4x4& other) const;
    ImVec3 operator*(const ImVec3& point) const;

    // Dostêp do elementów
    float& operator()(int row, int col);
    float operator()(int row, int col) const;

    // Macierz transponowana
    Matrix4x4 Transpose() const;

    // Debugowanie
    void Print() const;

private:
    float m[16]; // Macierz w porz¹dku kolumnowym (column-major)
};