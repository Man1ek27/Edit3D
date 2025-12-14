#include "Sphere.h"

Sphere::Sphere()
    : SceneObject("Sphere", ObjectType::SPHERE),
    radius(1.0f), slices(16), stacks(12) {
    GenerateVertices();
}

Sphere::Sphere(const std::string& name, float radius)
    : SceneObject(name, ObjectType::SPHERE),
    radius(radius), slices(16), stacks(12){
    GenerateVertices();
}

Sphere::Sphere(const std::string& name, const ImVec3& position, const ImVec3& rotation,
    const ImVec3& scale, float radius)
    : SceneObject(name, position, rotation, scale, ObjectType::SPHERE),
    radius(radius), slices(16), stacks(12) {
    GenerateVertices();
}

void Sphere::SetRadius(float newRadius) {
    if (newRadius > 0) {
        radius = newRadius;
        GenerateVertices();
    }
}

void Sphere::GenerateVertices() {
    localVertices.clear();
    wireframeEdges.clear();
    triangleIndices.clear();

    // Generowanie wierzcho³ków sfery (parametryzacja sferyczna)
    for (int i = 0; i <= stacks; ++i) {
        float phi = 3.14159265f * i / stacks; // Od 0 do pi

        for (int j = 0; j <= slices; ++j) {
            float theta = 2.0f * 3.14159265f * j / slices; // Od 0 do 2pi

            // Konwersja wspó³rzêdnych sferycznych na kartezjañskie
            float x = radius * std::sin(phi) * std::cos(theta);
            float y = radius * std::sin(phi) * std::sin(theta);
            float z = radius * std::cos(phi);

            localVertices.push_back(ImVec3(x, y, z));
        }
    }

    // Generowanie indeksów dla siatki (wireframe)
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int current = i * (slices + 1) + j;
            int next = current + 1;
            int below = (i + 1) * (slices + 1) + j;
            int belowNext = below + 1;

            // Poziome linie (równole¿niki)
            wireframeEdges.push_back(ImVec2(current, next));

            // Pionowe linie (po³udniki)
            wireframeEdges.push_back(ImVec2(current, below));

            // Przek¹tne dla trójk¹tów (dla przysz³ego wype³nienia)
            if (i < stacks - 1 && j < slices) {
                std::vector<int> tri1 = { current, next, belowNext };
                std::vector<int> tri2 = { current, belowNext, below };
                triangleIndices.push_back(tri1);
                triangleIndices.push_back(tri2);
            }
        }
    }

    // Dodaj ostatni segment poziomy
    for (int i = 0; i < stacks; ++i) {
        int current = (i + 1) * (slices + 1) - 1;
        int next = (i + 1) * (slices + 1);
        wireframeEdges.push_back(ImVec2(current, next));
    }
}

// Pomocnicza funkcja do rzutowania 3D na 2D (ta sama co w Box.cpp i Line.cpp)
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

void Sphere::Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
    float cam_rotX, float cam_rotY, float cam_zoom,
    bool show_vertices, bool show_edges) const {

    if (!IsVisible()) return;

    // Kolor sfery (jeœli jest zaznaczona, inny kolor)
    ImColor edge_color =  GetEdgeColor();
    ImColor vertex_color =  GetVertexColor();

    // Transformujemy wszystkie wierzcho³ki sfery do przestrzeni œwiata i rzutujemy na 2D
    std::vector<ImVec2> projectedVertices;
    projectedVertices.reserve(localVertices.size());

    for (const auto& localVertex : localVertices) {
        // 1. Transformacja obiektu (pozycja, rotacja, skala)
        ImVec3 worldVertex = TransformPoint(localVertex);

        // 2. Transformacja kamery (obrót)
        ImVec3 cameraVertex = RotateCameraPoint(worldVertex, cam_rotX, cam_rotY);

        // 3. Rzutowanie na 2D
        projectedVertices.push_back(ProjectPoint(cameraVertex, view_center, view_scale, cam_zoom));
    }

    // Rysowanie krawêdzi (siatka sfery)
    if (show_edges) {
        for (const auto& edge : wireframeEdges) {
            int idx1 = static_cast<int>(edge.x);
            int idx2 = static_cast<int>(edge.y);

            if (idx1 < projectedVertices.size() && idx2 < projectedVertices.size()) {
                // Cienka linia dla sfery
                draw_list->AddLine(
                    projectedVertices[idx1],
                    projectedVertices[idx2],
                    edge_color,
                    1.0f
                );
            }
        }
        
    }

    // Rysowanie wierzcho³ków
    if (show_vertices) {
        // Rysujemy tylko niektóre wierzcho³ki, ¿eby nie zaœmiecaæ widoku
        float vertex_size =  2.0f;

        // Rysuj co 4 wierzcho³ek
        for (size_t i = 0; i < projectedVertices.size(); i += 4) {
            draw_list->AddCircleFilled(projectedVertices[i], vertex_size, vertex_color);
        }
    }

    // Dodatkowo narysuj œrodek sfery
    
}