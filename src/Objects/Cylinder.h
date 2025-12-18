#pragma once

#include "SceneObject.h"

class Cylinder : public SceneObject {
public:
    // Konstruktory
    Cylinder();
    Cylinder(const std::string& name, float radius = 1.0f, float height = 2.0f);
    Cylinder(const std::string& name, const ImVec3& position, const ImVec3& rotation,
        const ImVec3& scale, float radius = 1.0f, float height = 2.0f);

    // Implementacja metody rysowania
    virtual void Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
        float cam_rotX, float cam_rotY, float cam_zoom,
        bool show_vertices = true, bool show_edges = true) const override;
    
    void reloadCommandRecord() override;

    // Metody specyficzne dla Cylinder
    float GetRadius() const { return radius; }
    float GetHeight() const { return height; }
    void SetRadius(float newRadius);
    void SetHeight(float newHeight);

    // Ustawienia renderowania
    void SetSegments(int segments) { this->segments = std::max(3, segments); GenerateVertices(); }
    int GetSegments() const { return segments; }

    void DrawTopBase(bool draw) { drawTopBase = draw; }
    bool GetDrawTopBase() const { return drawTopBase; }

    void DrawBottomBase(bool draw) { drawBottomBase = draw; }
    bool GetDrawBottomBase() const { return drawBottomBase; }

private:
    void GenerateVertices(); // Generuje wierzcho³ki walca

    float radius;           // Promieñ podstaw walca
    float height;           // Wysokoœæ walca
    int segments;           // Liczba segmentów podstawy
    bool drawTopBase;       // Czy rysowaæ górn¹ podstawê
    bool drawBottomBase;    // Czy rysowaæ doln¹ podstawê

    std::vector<ImVec3> topVertices;    // Wierzcho³ki górnej podstawy
    std::vector<ImVec3> bottomVertices; // Wierzcho³ki dolnej podstawy
};