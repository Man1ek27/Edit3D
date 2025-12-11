#pragma once

#include "PCH.h"
#include "SceneObject.h"

class Renderer3D {
public:
    Renderer3D();

    // Zmiana - teraz przyjmuje wektor obiektów jako parametr
    void Draw3DView(const std::vector<std::unique_ptr<SceneObject>>& objects);

    // Publiczne zmienne do kontroli z zewn¹trz (np. z Application)
    float rotationX; //TODO!: raczej robimy prywatne zmienne i gettery i settery ############### - Maniek - imo to tutaj mo¿na zostawiæ publiczne - wojtek
    float rotationY;
    float zoom;


private:
    ImVec2 project3DTo2D(const ImVec3& point, const ImVec2& center, float scale);
    ImVec3 rotatePoint(const ImVec3& point, float rotX, float rotY);
    void handleViewportInteraction();


    ImVec2 viewportSize;
    ImVec2 singleViewSize;

    struct ViewParam {
        float rotX, rotY;
        std::string name;
    };

    std::array<ViewParam, 4> views;

   
};