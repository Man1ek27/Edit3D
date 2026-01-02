#include "Render.h"

Renderer3D::Renderer3D()
    : rotationX(148.0f), rotationY(128.0f), zoom(0.2f), viewportSize(ImVec2(400, 400)),

    // inicjalizacja views
    views{ {
            // Kolejnoœæ i liczba elementów MUSI zgadzaæ siê z rozmiarem 4
            { 90.0f, 0.0f, "Widok Gora" },
            { 0.0f, 90.0f, "Widok Bok" },
            { 0.0f, 0.0f, "Widok Przod" },
            { rotationX, rotationY, "Widok Perspektywa" }
          } } {


    
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
    }
}



void Renderer3D::Draw3DView(const std::vector<std::unique_ptr<SceneObject>>& objects) {
    ImGui::SetNextWindowSize(ImVec2(1200, 850), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Widok 3D", nullptr,
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::Text("RotationX: %.2f, RotationY: %.2f", rotationX, rotationY);

    // Rysowanie poszczególnych view
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            ImGui::SetCursorPosX(ImGui::GetCursorStartPos().x + 150);
        }

        ImGui::BeginChild(views[i].name.c_str(), viewportSize, true,
            ImGuiWindowFlags_NoScrollbar);
        ImGui::Text("** %s **", views[i].name.c_str());
        ImGui::Text("** %f - %f **", views[i].rotX, views[i].rotY);
        ImGui::Separator();

        if (i == 3) {
            views[i].rotX = rotationX;
            views[i].rotY = rotationY;
            handleViewportInteraction();
        }

        ImVec2 viewportPos = ImGui::GetCursorScreenPos();
        ImVec2 center(viewportPos.x + viewportSize.x * 0.5f,
            viewportPos.y + viewportSize.y * 0.5f);
        //INFO: Tutaj kontrolujemy, jak "daleko" jest kamera.
        float scale = std::min(viewportSize.x, viewportSize.y) * 0.15f;

        // Rysowanie obiektów z przekazanego wektora
        for (const auto& obj : objects) {
            if (i == 3) { // Widok perspektywiczny
                obj->Draw(ImGui::GetWindowDrawList(), center, scale,
                    views[i].rotX, views[i].rotY, zoom);
            }
            else { // Widoki ortogonalne
                obj->Draw(ImGui::GetWindowDrawList(), center, scale,
                    views[i].rotX, views[i].rotY, 0.0f);
            }
        }

        ImGui::EndChild();

        if (i % 2 == 0) {
            ImGui::SameLine();
        }
    }

    ImGui::End();
}