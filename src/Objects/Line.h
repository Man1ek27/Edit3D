#pragma once
#include "PCH.h"
#include "SceneObject.h"

class Line : public SceneObject {
public:
    // Konstruktory
    Line();
    Line(const std::string& name);
    Line(const std::string& name, const ImVec3& start, const ImVec3& end);
    Line(const std::string& name, const ImVec3& position, const ImVec3& rotation,
        const ImVec3& scale, const ImVec3& start, const ImVec3& end);

    // Implementacja metody rysowania
    virtual void Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
        float cam_rotX, float cam_rotY, float cam_zoom,
        bool show_vertices = true, bool show_edges = true) const override;

    // Metody specyficzne dla Line
    const ImVec3& GetStartPoint() const { return localStart; }
    const ImVec3& GetEndPoint() const { return localEnd; }
    void SetStartPoint(const ImVec3& start) { localStart = start; }
    void SetEndPoint(const ImVec3& end) { localEnd = end; }

    // D³ugoœæ linii
    float GetLength() const;

private:
    ImVec3 localStart; // Pocz¹tkowy punkt w lokalnym uk³adzie wspó³rzêdnych
    ImVec3 localEnd;   // Koñcowy punkt w lokalnym uk³adzie wspó³rzêdnych
};