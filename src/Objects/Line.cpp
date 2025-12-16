#include "Line.h"

Line::Line()
    : SceneObject("Line", ObjectType::LINE),
    localStart(-0.5f, 0.0f, 0.0f),
    localEnd(0.5f, 0.0f, 0.0f) {
}

Line::Line(const std::string& name)
    : SceneObject(name, ObjectType::LINE),
    localStart(-0.5f, 0.0f, 0.0f),
    localEnd(0.5f, 0.0f, 0.0f) {
}

Line::Line(const std::string& name, const ImVec3& start, const ImVec3& end)
    : SceneObject(name, ObjectType::LINE),
    localStart(start),
    localEnd(end) {
}

Line::Line(const std::string& name, const ImVec3& position, const ImVec3& rotation,
    const ImVec3& scale, const ImVec3& start, const ImVec3& end)
    : SceneObject(name, position, rotation, scale, ObjectType::LINE),
    localStart(start),
    localEnd(end) {
}

float Line::GetLength() const {
    float dx = localEnd.x - localStart.x;
    float dy = localEnd.y - localStart.y;
    float dz = localEnd.z - localStart.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Pomocnicza funkcja do rzutowania 3D na 2D (ta sama co w Box.cpp, ale dodajemy tutaj dla kompletnoœci)
static ImVec2 ProjectPoint(const ImVec3& point, const ImVec2& center, float scale, float zoom) {
    // Proste rzutowanie perspektywiczne
    float factor = 2.0f / (2.0f + point.z * zoom);
    float x = point.x * factor * scale;
    float y = point.y * factor * scale;

    return ImVec2(center.x + x, center.y - y); // Oœ Y jest odwrócona w oknie
}

// Pomocnicza funkcja do obracania punktu (kamera)
static ImVec3 RotateCameraPoint(const ImVec3& point, float rotX, float rotY) {
    float radX = rotX * M_PI / 180.0f;
    float radY = rotY * M_PI / 180.0f;

    float cosX = std::cos(radX);
    float sinX = std::sin(radX);
    float cosY = std::cos(radY);
    float sinY = std::sin(radY);

    // Obrot wokó³ osi Y
    float x1 = point.x * cosY - point.z * sinY;
    float z1 = point.x * sinY + point.z * cosY;
    float y1 = point.y;

    // Obrot wokó³ osi X
    float y2 = y1 * cosX - z1 * sinX;
    float z2 = y1 * sinX + z1 * cosX;

    return ImVec3(x1, y2, z2);
}

void Line::Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
    float cam_rotX, float cam_rotY, float cam_zoom,
    bool show_vertices, bool show_edges) const {

    if (!IsVisible()) return;

    // Kolor linii (jeœli jest zaznaczona, inny kolor)
    ImColor line_color =  GetEdgeColor();
    ImColor vertex_color = GetVertexColor();

    // Transformujemy punkty linii do przestrzeni œwiata
    ImVec3 worldStart = TransformPoint(localStart);
    ImVec3 worldEnd = TransformPoint(localEnd);

    // Transformacja kamery
    ImVec3 cameraStart = RotateCameraPoint(worldStart, cam_rotX, cam_rotY);
    ImVec3 cameraEnd = RotateCameraPoint(worldEnd, cam_rotX, cam_rotY);

    // Rzutowanie na 2D
    ImVec2 screenStart = ProjectPoint(cameraStart, view_center, view_scale, cam_zoom);
    ImVec2 screenEnd = ProjectPoint(cameraEnd, view_center, view_scale, cam_zoom);

    // Rysowanie linii (krawêdzi)
    if (show_edges) {
        // Gruboœæ linii mo¿e zale¿eæ od tego, czy obiekt jest zaznaczony
        float thickness =  2.0f;
        draw_list->AddLine(screenStart, screenEnd, line_color, thickness);
    }

    // Rysowanie wierzcho³ków (punktów koñcowych linii)
    if (show_vertices) {
        float radius =  3.5f;
        draw_list->AddCircleFilled(screenStart, radius, vertex_color);
        draw_list->AddCircleFilled(screenEnd, radius, vertex_color);
    }
}


void Line::reloadCommandRecord(){
    this->commandRecord = std::format("LINE ({}, {}, {}) {}", position.x, position.y, position.z, this->GetLength());
}
