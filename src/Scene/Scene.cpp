#include "Scene.h"


void Scene::drawScene() {
    // Rysowanie widoku 3D przez dedykowany renderer
    renderer3D.Draw3DView();

    // Panel kontrolny
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(700, 50), ImGuiCond_FirstUseEver);

    ImGui::Begin("Kontrola 3D");
    ImGui::SliderFloat("Obrot X", &renderer3D.rotationX, 0.0f, 360.0f); // czytelny format z wcieciem - Maniek
    ImGui::SliderFloat("Obrot Y", &renderer3D.rotationY, 0.0f, 360.0f);
    ImGui::SliderFloat("Powiekszenie", &renderer3D.zoom, 0.125f, 1.0f);
    if (ImGui::Button("Resetuj widok")) {
        renderer3D.rotationX = 148.0f;
        renderer3D.rotationY = 128.0f;
        renderer3D.zoom = 0.5f;
    }
    ImGui::End();

    console.Draw();
}