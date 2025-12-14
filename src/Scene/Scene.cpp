#include "Scene.h"


Scene::Scene(): console(*this){}


void Scene::drawScene() {
    // Rysowanie widoku 3D przez dedykowany renderer
    renderer3D.Draw3DView(objects);
    ImGui::SameLine();

    // Panel kontrolny
    //ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
    //ImGui::SetNextWindowPos(ImVec2(700, 50), ImGuiCond_FirstUseEver);

    /*ImGui::Begin("Kontrola 3D"); - JU¯ NIEPOTRZEBNE
    ImGui::SliderFloat("Obrot X", &renderer3D.rotationX, 0.0f, 360.0f);
    ImGui::SliderFloat("Obrot Y", &renderer3D.rotationY, 0.0f, 360.0f);
    ImGui::SliderFloat("Powiekszenie", &renderer3D.zoom, 0.125f, 1.0f);
    if (ImGui::Button("Resetuj widok")) {
        renderer3D.rotationX = 148.0f;
        renderer3D.rotationY = 128.0f;
        renderer3D.zoom = 0.5f;
    }
    ImGui::End();*/ 


    //Rejestrator
    ImGui::SetNextWindowSize(ImVec2(420, 850), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(1200, 0), ImGuiCond_FirstUseEver);
    ImGui::Begin("Recorder", nullptr,
        ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::Text("RECORDER:");

        for (const auto& obj : objects) {
            ImGui::Text("\t%d %s", obj->GetId(), obj->GetCommandRecord().c_str());
        }
    ImGui::End();

    console.Draw();
}

void Scene::AddObject(std::unique_ptr<SceneObject> object) {
    objects.push_back(std::move(object));
}

void Scene::RemoveObject(unsigned int objectId) {
    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [objectId](const std::unique_ptr<SceneObject>& obj) {
                return obj->GetId() == objectId;
            }),
        objects.end()
    );
}

void Scene::ClearObjects() {
    objects.clear();
}

std::optional<unsigned> Scene::indexFromId(int id) const {
    unsigned index = 0;
    for (const auto& obj : objects) {
        if (obj->GetId() == id)
            return index;
        index++;
    }
    return std::nullopt; 
}



void Scene::MoveObject(unsigned int objectId, ImVec3& newPos) {
    auto result = this->indexFromId(objectId);
    ImVec3 oldPos = objects[result.value()]->GetPosition();
    if (result.has_value()) {
        objects[result.value()]->SetPosition(ImVec3(oldPos.x+newPos.x, oldPos.y + newPos.y, oldPos.z + newPos.z));
    }
    else {
        std::cout << "Error no object with this id" << std::endl;
    }
}

void Scene::RotateObject(unsigned int objectId, ImVec3& point, ImVec3& newRot) { // - TO DO - tu przeba to jakoœ ³adnie zrobiæ bo mamy rotowaæ wzglêdem punktu poin o k¹ty newRot(alfa, beta, delta)
    auto result = this->indexFromId(objectId);
    ImVec3 oldRot = objects[result.value()]->GetRotation();
    if (result.has_value()) {
        objects[result.value()]->SetPosition(ImVec3(oldRot.x + newRot.x, oldRot.y + newRot.y, oldRot.z + newRot.z));
    }
    else {
        std::cout << "Error no object with this id" << std::endl;
    }
}
