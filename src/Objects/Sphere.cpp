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

void Sphere::reloadCommandRecord() {
    //sphere->setCommandRecord(std::format("SPHERE ({}, {}, {}) {} ({} {})", p0.x, p0.y, p0.z, r, nm.x, nm.y));

    this->commandRecord = std::format("SPHERE ({}, {}, {}) R: {} ", position.x, position.y, position.z, radius);
}