#include "Cylinder.h"

Cylinder::Cylinder()
    : SceneObject("Cylinder", ObjectType::CUSTOM),
    radius(1.0f), height(2.0f), segments(16),
    drawTopBase(true), drawBottomBase(true) {
    GenerateVertices();
}

Cylinder::Cylinder(const std::string& name, float radius, float height)
    : SceneObject(name, ObjectType::CUSTOM),
    radius(radius), height(height), segments(16),
    drawTopBase(true), drawBottomBase(true) {
    GenerateVertices();
}

Cylinder::Cylinder(const std::string& name, const ImVec3& position, const ImVec3& rotation,
    const ImVec3& scale, float radius, float height)
    : SceneObject(name, position, rotation, scale, ObjectType::CUSTOM),
    radius(radius), height(height), segments(16),
    drawTopBase(true), drawBottomBase(true) {
    GenerateVertices();
}

void Cylinder::SetRadius(float newRadius) {
    if (newRadius > 0) {
        radius = newRadius;
        GenerateVertices();
    }
}

void Cylinder::SetHeight(float newHeight) {
    if (newHeight > 0) {
        height = newHeight;
        GenerateVertices();
    }
}

void Cylinder::GenerateVertices() {
    topVertices.clear();
    bottomVertices.clear();

    // Generowanie wierzcho³ków górnej podstawy (y = height/2)
    // Generowanie wierzcho³ków dolnej podstawy (y = -height/2)
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * 3.14159265f * i / segments;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        // Wierzcho³ki górnej podstawy
        topVertices.push_back(ImVec3(x, height / 2.0f, z));

        // Wierzcho³ki dolnej podstawy
        bottomVertices.push_back(ImVec3(x, -height / 2.0f, z));
    }
}

void Cylinder::Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
    float cam_rotX, float cam_rotY, float cam_zoom,
    bool show_vertices, bool show_edges) const {

    if (!IsVisible()) return;

    // Kolor walca (jeœli jest zaznaczony, inny kolor)
    ImColor edge_color = GetEdgeColor();
    ImColor vertex_color = GetVertexColor();

    // Transformujemy i rzutujemy wierzcho³ki górnej podstawy
    std::vector<ImVec2> screenTopVertices;
    screenTopVertices.reserve(topVertices.size());

    for (const auto& topVertex : topVertices) {
        ImVec3 worldVertex = TransformPoint(topVertex);
        ImVec3 cameraVertex = RotateCameraPoint(worldVertex, cam_rotX, cam_rotY);
        screenTopVertices.push_back(ProjectPoint(cameraVertex, view_center, view_scale, cam_zoom));
    }

    // Transformujemy i rzutujemy wierzcho³ki dolnej podstawy
    std::vector<ImVec2> screenBottomVertices;
    screenBottomVertices.reserve(bottomVertices.size());

    for (const auto& bottomVertex : bottomVertices) {
        ImVec3 worldVertex = TransformPoint(bottomVertex);
        ImVec3 cameraVertex = RotateCameraPoint(worldVertex, cam_rotX, cam_rotY);
        screenBottomVertices.push_back(ProjectPoint(cameraVertex, view_center, view_scale, cam_zoom));
    }

    // Rysowanie podstaw (jeœli w³¹czone)
    if (show_edges) {
        // Górna podstawa
        if (drawTopBase && screenTopVertices.size() > 1) {
            for (size_t i = 0; i < screenTopVertices.size() - 1; ++i) {
                draw_list->AddLine(screenTopVertices[i], screenTopVertices[i + 1], edge_color, 2.0f);
            }
            // Zamkniêcie okrêgu górnej podstawy
            draw_list->AddLine(screenTopVertices.back(), screenTopVertices[0], edge_color, 2.0f);
        }

        // Dolna podstawa
        if (drawBottomBase && screenBottomVertices.size() > 1) {
            for (size_t i = 0; i < screenBottomVertices.size() - 1; ++i) {
                draw_list->AddLine(screenBottomVertices[i], screenBottomVertices[i + 1], edge_color, 2.0f);
            }
            // Zamkniêcie okrêgu dolnej podstawy
            draw_list->AddLine(screenBottomVertices.back(), screenBottomVertices[0], edge_color, 2.0f);
        }

        // Rysowanie linii bocznych (³¹cz¹cych odpowiadaj¹ce sobie wierzcho³ki podstaw)
        size_t verticesToDraw = std::min(screenTopVertices.size(), screenBottomVertices.size());
        for (size_t i = 0; i < verticesToDraw; ++i) {
            draw_list->AddLine(screenTopVertices[i], screenBottomVertices[i], edge_color, 2.0f);
        }
    }

    // Rysowanie wierzcho³ków
    if (show_vertices) {
        float vertex_radius = 3.0f;

        // Wierzcho³ki górnej podstawy
        if (drawTopBase) {
            for (const auto& screenTopVertex : screenTopVertices) {
                draw_list->AddCircleFilled(screenTopVertex, vertex_radius, vertex_color);
            }
        }

        // Wierzcho³ki dolnej podstawy
        if (drawBottomBase) {
            for (const auto& screenBottomVertex : screenBottomVertices) {
                draw_list->AddCircleFilled(screenBottomVertex, vertex_radius, vertex_color);
            }
        }
    }


}


void Cylinder::reloadCommandRecord() {
    this->commandRecord = std::format("CYLINDER ({}, {}, {})  r: {} h: {}", position.x, position.y, position.z, radius, height);
}