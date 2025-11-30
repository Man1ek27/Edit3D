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

private:
    void drawCube(float rotX, float rotY); // Rysowanie samego szeœcianu
    ImVec2 project3DTo2D(const ImVec3& point, const ImVec2& center, float scale);
    ImVec3 rotatePoint(const ImVec3& point, float rotX, float rotY);
    void handleViewportInteraction();

    // Punkty szeœcianu 3D
    std::vector<ImVec3> cubeVertices;
    std::vector<ImVec2> cubeEdges; //czemu tu robisz vector::pair a nie vector::ImVec2 ?? - Zmieni³em, lepiej programistycznie to wygl¹da - Maniek

    ImVec2 viewportSize;
    ImVec2 singleViewSize;

    struct ViewParam {
        float rotX, rotY;
        std::string name;
    };

    std::array<ViewParam, 4> views;

    std::vector<SceneObject> objects; //to bedzie pojemnik na wszystkie obiekty które w têtli foreach bêdziemy rysowaæ póŸniej 
    // a ¿e po SceneObject bedzie dziwdziczy³ kazdy objekt to przejedziemy tylko jedn¹ pêtl¹ po tym i dal ka¿dego obiektu wywo³a .Draw() - ka¿dy obiek musi mieæ t¹ metodê o tej samej nazwie - Maniek

};