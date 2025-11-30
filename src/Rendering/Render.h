#pragma once

#include "PCH.h"

class Renderer3D {
public:
    Renderer3D();
    void Draw3DView(); // G³ówna funkcja rysuj¹ca widok 3D

    // Publiczne zmienne do kontroli z zewn¹trz (np. z Application)
    float rotationX;
    float rotationY;
    float zoom;

private:
    void drawCube(); // Rysowanie samego szeœcianu
    ImVec2 project3DTo2D(const ImVec3& point, const ImVec2& center, float scale);
    ImVec3 rotatePoint(const ImVec3& point, float rotX, float rotY);
    void handleViewportInteraction();

    // Punkty szeœcianu 3D
    std::vector<ImVec3> cubeVertices;
    std::vector<std::pair<int, int>> cubeEdges;

    ImVec2 viewportSize;
};