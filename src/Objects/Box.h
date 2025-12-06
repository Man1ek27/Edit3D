#pragma once

#include "SceneObject.h"

class Box : public SceneObject {
public:
    // Konstruktory
    Box();
    Box(const std::string& name, float size = 1.0f);
    Box(const std::string& name, const ImVec3& position, const ImVec3& rotation,
        const ImVec3& scale, float size = 1.0f);

    // Implementacja metody rysowania
    virtual void Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
        float cam_rotX, float cam_rotY, float cam_zoom,
        bool show_vertices = true, bool show_edges = true) const override;

    // Metody specyficzne dla Box
    float GetSize() const { return size; }
    void SetSize(float newSize) { size = newSize; GenerateVertices(); }

private:
    void GenerateVertices(); // Generuje wierzcho³ki szeœcianu

    float size; // Rozmiar boku szeœcianu (domyœlnie od -size/2 do size/2)
    std::vector<ImVec3> localVertices; // Wierzcho³ki w lokalnym uk³adzie wspó³rzêdnych
    std::vector<ImVec2> edges; // Definicja krawêdzi (indeksy wierzcho³ków)
};