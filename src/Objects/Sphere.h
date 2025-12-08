#pragma once

#include "PCH.h"
#include "SceneObject.h"


class Sphere : public SceneObject {
public:
    // Konstruktory
    Sphere();
    Sphere(const std::string& name, float radius = 1.0f);
    Sphere(const std::string& name, const ImVec3& position, const ImVec3& rotation,
        const ImVec3& scale, float radius = 1.0f);

    // Implementacja metody rysowania
    virtual void Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
        float cam_rotX, float cam_rotY, float cam_zoom,
        bool show_vertices = true, bool show_edges = true) const override;

    // Metody specyficzne dla Sphere
    float GetRadius() const { return radius; }
    void SetRadius(float newRadius);


    void SetSlices(int slices) { this->slices = std::max(3, slices); GenerateVertices(); }
    int GetSlices() const { return slices; }

    void SetStacks(int stacks) { this->stacks = std::max(2, stacks); GenerateVertices(); }
    int GetStacks() const { return stacks; }

private:
    void GenerateVertices(); // Generuje wierzcho³ki sfery

    float radius;           // Promieñ sfery
    int slices;             // Liczba segmentów w poziomie (d³ugoœæ geograficzna)
    int stacks;             // Liczba segmentów w pionie (szerokoœæ geograficzna)

    std::vector<ImVec3> localVertices; // Wierzcho³ki sfery w lokalnym uk³adzie wspó³rzêdnych
    std::vector<ImVec2> wireframeEdges; // Krawêdzie siatki (dla trybu wireframe)
    std::vector<std::vector<int>> triangleIndices; // Indeksy trójk¹tów (dla przysz³ego wype³nienia)
};