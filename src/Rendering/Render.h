#pragma once

#include "PCH.h"
#include "SceneObject.h"

class Renderer3D {
public:
    Renderer3D();
    void Draw3DView(); // G³ówna funkcja rysuj¹ca widok 3D

    // Publiczne zmienne do kontroli z zewn¹trz (np. z Application)
    float rotationX; //TODO!: raczej robimy prywatne zmienne i gettery i settery ############### - Maniek
    float rotationY;
    float zoom;

    void AddObject(std::unique_ptr<SceneObject> object);
    void RemoveObject(unsigned int objectId);
    void ClearObjects();
    size_t GetObjectCount() const { return objects.size(); }

private:
    std::vector<std::unique_ptr<SceneObject>> objects;

private:
    void drawCube(float rotX, float rotY); // Rysowanie samego szeœcianu
    ImVec2 project3DTo2D(const ImVec3& point, const ImVec2& center, float scale);
    ImVec3 rotatePoint(const ImVec3& point, float rotX, float rotY);
    void handleViewportInteraction();

    //DEPRECATED
    // Punkty szeœcianu 3D
    //std::vector<ImVec3> cubeVertices;
    //std::vector<ImVec2> cubeEdges; 

    ImVec2 viewportSize;
    ImVec2 singleViewSize;

    struct ViewParam {
        float rotX, rotY;
        std::string name;
    };

    std::array<ViewParam, 4> views;

   
};