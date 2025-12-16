#include "Box.h"


Box::Box()
    : SceneObject("Box", ObjectType::BOX), size(1.0f) {
    GenerateVertices();
}

Box::Box(const std::string& name, float size)
    : SceneObject(name, ObjectType::BOX), size(size) {
    GenerateVertices();
}

Box::Box(const std::string& name, const ImVec3& position, const ImVec3& rotation,
    const ImVec3& scale, float size)
    : SceneObject(name, position, rotation, scale, ObjectType::BOX), size(size) {
    GenerateVertices();
}

void Box::GenerateVertices() {
    localVertices.clear();

    // Tworzymy 8 wierzcho³ków szeœcianu (œrodek w (0,0,0))
    float halfSize = size / 2.0f;

    // Dolna œciana (z = -halfSize)
    localVertices.push_back(ImVec3(-halfSize, -halfSize, -halfSize)); // 0: tylny dolny lewy
    localVertices.push_back(ImVec3(halfSize, -halfSize, -halfSize)); // 1: tylny dolny prawy
    localVertices.push_back(ImVec3(halfSize, halfSize, -halfSize)); // 2: tylny górny prawy
    localVertices.push_back(ImVec3(-halfSize, halfSize, -halfSize)); // 3: tylny górny lewy

    // Górna œciana (z = halfSize)
    localVertices.push_back(ImVec3(-halfSize, -halfSize, halfSize));  // 4: przedni dolny lewy
    localVertices.push_back(ImVec3(halfSize, -halfSize, halfSize));  // 5: przedni dolny prawy
    localVertices.push_back(ImVec3(halfSize, halfSize, halfSize));  // 6: przedni górny prawy
    localVertices.push_back(ImVec3(-halfSize, halfSize, halfSize));  // 7: przedni górny lewy

    // Definicja krawêdzi (12 krawêdzi szeœcianu)
    edges.clear();
    edges.push_back(ImVec2(0, 1)); // Tylna dolna
    edges.push_back(ImVec2(1, 2)); // Tylna prawa
    edges.push_back(ImVec2(2, 3)); // Tylna górna
    edges.push_back(ImVec2(3, 0)); // Tylna lewa

    edges.push_back(ImVec2(4, 5)); // Przednia dolna
    edges.push_back(ImVec2(5, 6)); // Przednia prawa
    edges.push_back(ImVec2(6, 7)); // Przednia górna
    edges.push_back(ImVec2(7, 4)); // Przednia lewa

    edges.push_back(ImVec2(0, 4)); // Lewa dolna
    edges.push_back(ImVec2(1, 5)); // Prawa dolna
    edges.push_back(ImVec2(2, 6)); // Prawa górna
    edges.push_back(ImVec2(3, 7)); // Lewa górna
}

// Pomocnicza funkcja do rzutowania 3D na 2D
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

void Box::Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
    float cam_rotX, float cam_rotY, float cam_zoom,
    bool show_vertices, bool show_edges) const {

    if (!IsVisible()) return;

    ImColor edge_color =  GetEdgeColor();
    ImColor vertex_color =  GetVertexColor();

    // Transformujemy wszystkie wierzcho³ki do przestrzeni œwiata i rzutujemy na 2D
    std::vector<ImVec2> projectedVertices;

    for (const auto& localVertex : localVertices) {
        // 1. Transformacja obiektu (pozycja, rotacja, skala)
        ImVec3 worldVertex = TransformPoint(localVertex);

        // 2. Transformacja kamery (obrót)
        ImVec3 cameraVertex = RotateCameraPoint(worldVertex, cam_rotX, cam_rotY);

        // 3. Rzutowanie na 2D
        projectedVertices.push_back(ProjectPoint(cameraVertex, view_center, view_scale, cam_zoom));
    }

    // Rysowanie krawêdzi
    if (show_edges) {
        for (const auto& edge : edges) {
            int idx1 = static_cast<int>(edge.x);
            int idx2 = static_cast<int>(edge.y);

            if (idx1 < projectedVertices.size() && idx2 < projectedVertices.size()) {
                draw_list->AddLine(
                    projectedVertices[idx1],
                    projectedVertices[idx2],
                    edge_color,
                    2.0f
                );
            }
        }
    }

    // Rysowanie wierzcho³ków
    if (show_vertices) {
        for (const auto& vertex : projectedVertices) {
            draw_list->AddCircleFilled(vertex, 4.0f, vertex_color);
        }
    }
}


void Box::reloadCommandRecord() {
    //box->setCommandRecord(std::format("BOX ({}, {}, {}) ({}, {}, {})", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z));

    this->commandRecord = std::format("BOX ({}, {}, {}) a: {}", position.x, position.y, position.z, size);
}