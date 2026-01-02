#include "Cone.h"

Cone::Cone()
    : SceneObject("Cone", ObjectType::CONE),
    radius(1.0f), height(2.0f), segments(16), drawBase(true),
    apex(0.0f, height / 2.0f, 0.0f) {
    GenerateVertices();
}

Cone::Cone(const std::string& name, float radius, float height)
    : SceneObject(name, ObjectType::CONE),
    radius(radius), height(height), segments(16), drawBase(true),
    apex(0.0f, height / 2.0f, 0.0f) {
    GenerateVertices();
}

Cone::Cone(const std::string& name, const ImVec3& position, const ImVec3& rotation,
    const ImVec3& scale, float radius, float height)
    : SceneObject(name, position, rotation, scale, ObjectType::CONE),
    radius(radius), height(height), segments(16), drawBase(true),
    apex(0.0f, height / 2.0f, 0.0f) {
    GenerateVertices();
}

void Cone::SetRadius(float newRadius) {
    if (newRadius > 0) {
        radius = newRadius;
        GenerateVertices();
    }
}

void Cone::SetHeight(float newHeight) {
    if (newHeight > 0) {
        height = newHeight;
        apex = ImVec3(0.0f, height / 2.0f, 0.0f);
        GenerateVertices();
    }
}

void Cone::GenerateVertices() {
    baseVertices.clear();
    sideVertices.clear();

    // Generowanie wierzcho³ków podstawy (ko³o w p³aszczyŸnie XZ)
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * 3.14159265f * i / segments;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        // Wierzcho³ki podstawy (y = -height/2)
        baseVertices.push_back(ImVec3(x, -height / 2.0f, z));

        // Dla boków sto¿ka - punkty ³¹cz¹ce podstawê z wierzcho³kiem
        if (i < segments) {
            sideVertices.push_back(baseVertices.back());
            sideVertices.push_back(apex);
        }
    }

    // Dodaj pierwszy wierzcho³ek ponownie, aby zamkn¹æ podstawê
    if (segments > 0) {
        sideVertices.push_back(baseVertices[0]);
        sideVertices.push_back(apex);
    }
}

void Cone::Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
    float cam_rotX, float cam_rotY, float cam_zoom,
    bool show_vertices, bool show_edges) const {

    if (!IsVisible()) return;

    // Kolor sto¿ka (jeœli jest zaznaczony, inny kolor)
    ImColor edge_color =  GetEdgeColor();
    ImColor vertex_color = GetVertexColor();

    // Transformujemy punkty sto¿ka do przestrzeni œwiata
    ImVec3 worldApex = TransformPoint(apex);

    // Rzutujemy i obracamy punkty kamery
    ImVec3 cameraApex = RotateCameraPoint(worldApex, cam_rotX, cam_rotY);
    ImVec2 screenApex = ProjectPoint(cameraApex, view_center, view_scale, cam_zoom);

    // Transformujemy i rzutujemy punkty podstawy
    std::vector<ImVec2> screenBaseVertices;
    screenBaseVertices.reserve(baseVertices.size());

    for (const auto& baseVertex : baseVertices) {
        ImVec3 worldVertex = TransformPoint(baseVertex);
        ImVec3 cameraVertex = RotateCameraPoint(worldVertex, cam_rotX, cam_rotY);
        screenBaseVertices.push_back(ProjectPoint(cameraVertex, view_center, view_scale, cam_zoom));
    }

    // Rysowanie podstawy (jeœli w³¹czone)
    if (show_edges && drawBase && screenBaseVertices.size() > 1) {
        for (size_t i = 0; i < screenBaseVertices.size() - 1; ++i) {
            draw_list->AddLine(screenBaseVertices[i], screenBaseVertices[i + 1], edge_color, 2.0f);
        }
        // Zamkniêcie okrêgu podstawy
        draw_list->AddLine(screenBaseVertices.back(), screenBaseVertices[0], edge_color, 2.0f);
    }

    // Rysowanie boków sto¿ka
    if (show_edges) {
        for (const auto& screenBaseVertex : screenBaseVertices) {
            draw_list->AddLine(screenBaseVertex, screenApex, edge_color, 2.0f);
        }
    }

    // Rysowanie wierzcho³ków
    if (show_vertices) {
        // Wierzcho³ek sto¿ka
        float apex_radius = 3.5f;
        draw_list->AddCircleFilled(screenApex, apex_radius, vertex_color);

        // Wierzcho³ki podstawy
        float base_radius = 3.0f;
        for (const auto& screenBaseVertex : screenBaseVertices) {
            draw_list->AddCircleFilled(screenBaseVertex, base_radius, vertex_color);
        }
    }

}

void Cone::reloadCommandRecord() {
    //cone->setCommandRecord(std::format("CONE ({}, {}, {}) r1: {} ({}, {}, {}) r2: {}", p1.x, p1.y, p1.z,r1,  p2.x, p2.y, p2.z, r2));

    this->commandRecord = std::format("CONE ({}, {}, {}) r: {} h: {}", position.x, position.y, position.z, radius, height);
}