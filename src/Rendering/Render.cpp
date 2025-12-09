#include "Render.h"

Renderer3D::Renderer3D()
    : rotationX(148.0f), rotationY(128.0f), zoom(0.5f), viewportSize(ImVec2(400, 400)),

    // inicjalizacja views
    views{ {
            // Kolejnoœæ i liczba elementów MUSI zgadzaæ siê z rozmiarem 4
            { 90.0f, 0.0f, "Widok Gora" },
            { 0.0f, 90.0f, "Widok Bok" },
            { 0.0f, 0.0f, "Widok Przod" },
            { rotationX, rotationY, "Widok Perspektywa" }
          } } {


    
}

void Renderer3D::AddObject(std::unique_ptr<SceneObject> object) {
    objects.push_back(std::move(object));
}

void Renderer3D::RemoveObject(unsigned int objectId) {
    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [objectId](const std::unique_ptr<SceneObject>& obj) {
                return obj->GetId() == objectId;
            }),
        objects.end()
    );
}

void Renderer3D::ClearObjects() {
    objects.clear();
}


// Funkcja do rzutowania 3D na 2D
ImVec2 Renderer3D::project3DTo2D(const ImVec3& point, const ImVec2& center, float scale) {
    // Proste rzutowanie perspektywiczne
    float factor = 2.0f / (2.0f + point.z * zoom);
    float x = point.x * factor * scale;
    float y = point.y * factor * scale;

    return ImVec2(center.x + x, center.y - y); // Oœ Y jest odwrócona w oknie
}

 //Funkcja do obracania punktu 3D
ImVec3 Renderer3D::rotatePoint(const ImVec3& point, float rotX, float rotY) {
    // U¿yj macierzy zamiast rêcznych obliczeñ
    Matrix4x4 rotYMat = Matrix4x4::RotationY(rotY);
    Matrix4x4 rotXMat = Matrix4x4::RotationX(rotX);

    // Kolejnoœæ: najpierw Y, potem X (jak w oryginalnym kodzie)
    Matrix4x4 combinedRot = rotYMat.Multiply(rotXMat);

    return combinedRot.TransformPoint(point);
}

void Renderer3D::handleViewportInteraction() {
    //INFO: Funkcja zwi¹zana z ruszaniem myszk¹ i zoomowaniem za pomoc¹ myszki.

    if (ImGui::IsWindowHovered()) {
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
            ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
            rotationY += delta.x * 0.5f;
            rotationX += delta.y * 0.5f;
            ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);
        }

        float wheel = ImGui::GetIO().MouseWheel;
        if (wheel != 0) {
            zoom += wheel * 0.1f;
            zoom = std::max(0.1f, std::min(zoom, 3.0f));
        }
    }
}



void Renderer3D::Draw3DView() {
    ImGui::SetNextWindowSize(ImVec2(1200, 850), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Widok 3D", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	    //DEBUG: Informacja o widocznoœci okna
        ImGui::Text("RotationX: %.2f, RotationY: %.2f", rotationX, rotationY);


        //viewportSize = ImGui::GetContentRegionAvail();

        
        //Ryzowanie poszczególnych view
        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0) {
                ImGui::SetCursorPosX(ImGui::GetCursorStartPos().x + 150);
            }
            ImGui::BeginChild(views[i].name.c_str(), viewportSize, true, ImGuiWindowFlags_NoScrollbar );
            ImGui::Text("** %s **", views[i].name.c_str());
            ImGui::Text("** %f - %f **", views[i].rotX, views[i].rotY);
            ImGui::Separator();


            if (i == 3) {
                views[i].rotX = rotationX;
                views[i].rotY = rotationY;

                // Obs³uga interakcji tylko dla perspective
                handleViewportInteraction();
            }
            //Wywo³anie odpowiedniego rysowania cube
            ImVec2 viewportPos = ImGui::GetCursorScreenPos();
            ImVec2 center(viewportPos.x + viewportSize.x * 0.5f, viewportPos.y + viewportSize.y * 0.5f);
            float scale = std::min(viewportSize.x, viewportSize.y) * 0.2f;

            //MARIUSZ INFO COMMENT TODO: SPRAWDZIÆ CZY OK ZAMYS£
            for (const auto& obj : objects) {
                if (i == 3) { // Widok perspektywiczny - ostatni
                    obj->Draw(ImGui::GetWindowDrawList(), center, scale,
                        views[i].rotX, views[i].rotY, zoom);
                }
                else { // Widoki ortogonalne
                    obj->Draw(ImGui::GetWindowDrawList(), center, scale,
                        views[i].rotX, views[i].rotY, 0.0f); // Brak zoom dla ortogonalnych
                }
            }

            ImGui::EndChild();

            if (i % 2 == 0) {
                ImGui::SameLine();
            }


        }
        
    ImGui::End();
}