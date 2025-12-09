#pragma once
#include "SceneObject.h"


class Cone : public SceneObject {
public:
    // Konstruktory
    Cone();
    Cone(const std::string& name, float radius = 1.0f, float height = 2.0f);
    Cone(const std::string& name, const ImVec3& position, const ImVec3& rotation,
        const ImVec3& scale, float radius = 1.0f, float height = 2.0f);

    // Implementacja metody rysowania
    virtual void Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
        float cam_rotX, float cam_rotY, float cam_zoom,
        bool show_vertices = true, bool show_edges = true) const override;

    // Metody specyficzne dla Cone
    float GetRadius() const { return radius; }
    float GetHeight() const { return height; }
    void SetRadius(float newRadius);
    void SetHeight(float newHeight);

    // Ustawienia renderowania
    void SetSegments(int segments) { this->segments = std::max(3, segments); GenerateVertices(); }
    int GetSegments() const { return segments; }

    void DrawBase(bool draw) { drawBase = draw; }
    bool GetDrawBase() const { return drawBase; }

private:
    void GenerateVertices(); // Generuje wierzcho³ki sto¿ka

    float radius;           // Promieñ podstawy sto¿ka
    float height;           // Wysokoœæ sto¿ka (od podstawy do wierzcho³ka)
    int segments;           // Liczba segmentów podstawy
    bool drawBase;          // Czy rysowaæ podstawê

    ImVec3 apex;            // Wierzcho³ek sto¿ka (w lokalnym uk³adzie)
    std::vector<ImVec3> baseVertices; // Wierzcho³ki podstawy sto¿ka
    std::vector<ImVec3> sideVertices; // Wierzcho³ki boków sto¿ka (dla transformacji)
};