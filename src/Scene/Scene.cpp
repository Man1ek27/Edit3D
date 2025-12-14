#include "Scene.h"


Scene::Scene(): console(*this){}


void Scene::drawScene() {
    // Rysowanie widoku 3D przez dedykowany renderer
    renderer3D.Draw3DView(objects);
    ImGui::SameLine();



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

void Scene::SaveToFile(const std::string& filename) {
    json sceneJson;

    // Informacje o scenie
    sceneJson["scene_info"] = {
        {"object_count", objects.size()},
        {"save_time", __TIMESTAMP__}
    };

    // Zapisz wszystkie obiekty
    json objectsArray = json::array();

    for (const auto& obj : objects) {
        try {
            json objJson = SceneObjectToJson(*obj);
            objectsArray.push_back(objJson);
        }
        catch (const std::exception& e) {
            std::cerr << "Error serializing object: " << e.what() << std::endl;
        }
    }

    sceneJson["objects"] = objectsArray;

    // Zapisz do pliku
    std::ofstream file(filename);
    if (file.is_open()) {
        file << sceneJson.dump(4); // Pretty print z 4 spacjami wciêcia
        std::cout << "Scene saved to " << filename << " with " << objects.size() << " objects." << std::endl;
    }
    else {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
    }
}

void Scene::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return;
    }

    try {
        json sceneJson;
        file >> sceneJson;

        // Wyczyœæ obecne obiekty
        ClearObjects();

        // Wczytaj obiekty
        if (sceneJson.contains("objects") && sceneJson["objects"].is_array()) {
            const auto& objectsArray = sceneJson["objects"];

            for (const auto& objJson : objectsArray) {
                try {
                    auto obj = JsonToSceneObject(objJson);
                    if (obj) {
                        AddObject(std::move(obj));
                    }
                }
                catch (const std::exception& e) {
                    std::cerr << "Error deserializing object: " << e.what() << std::endl;
                }
            }

            std::cout << "Scene loaded from " << filename << " with " << objects.size() << " objects." << std::endl;
        }
    }
    catch (const json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
}

json Scene::SceneObjectToJson(const SceneObject& obj) {
    json j;

    // Podstawowe w³aœciwoœci
    j["id"] = obj.GetId();
    j["name"] = obj.GetName();
    j["type"] = static_cast<int>(obj.GetType());
    j["visible"] = obj.IsVisible();

    // Transformacje
    const auto& pos = obj.GetPosition();
    const auto& rot = obj.GetRotation();
    const auto& scale = obj.GetScale();

    j["position"] = { pos.x, pos.y, pos.z };
    j["rotation"] = { rot.x, rot.y, rot.z };
    j["scale"] = { scale.x, scale.y, scale.z };

    // Kolory
    const auto& edgeColor = obj.GetEdgeColor();
    const auto& vertexColor = obj.GetVertexColor();

    j["edge_color"] = {
        {"r", edgeColor.Value.x * 255},
        {"g", edgeColor.Value.y * 255},
        {"b", edgeColor.Value.z * 255},
        {"a", edgeColor.Value.w * 255}
    };

    j["vertex_color"] = {
        {"r", vertexColor.Value.x * 255},
        {"g", vertexColor.Value.y * 255},
        {"b", vertexColor.Value.z * 255},
        {"a", vertexColor.Value.w * 255}
    };

    // Specyficzne w³aœciwoœci dla ka¿dego typu
    switch (obj.GetType()) {
    case ObjectType::BOX: {
        const Box* box = dynamic_cast<const Box*>(&obj);
        if (box) {
            j["size"] = box->GetSize();
        }
        break;
    }
    case ObjectType::SPHERE: {
        const Sphere* sphere = dynamic_cast<const Sphere*>(&obj);
        if (sphere) {
            j["radius"] = sphere->GetRadius();
            j["slices"] = sphere->GetSlices();
            j["stacks"] = sphere->GetStacks();
        }
        break;
    }
    case ObjectType::CONE: {
        const Cone* cone = dynamic_cast<const Cone*>(&obj);
        if (cone) {
            j["radius"] = cone->GetRadius();
            j["height"] = cone->GetHeight();
            j["segments"] = cone->GetSegments();
            j["draw_base"] = cone->GetDrawBase();
        }
        break;
    }
    case ObjectType::LINE: {
        const Line* line = dynamic_cast<const Line*>(&obj);
        if (line) {
            const auto& start = line->GetStartPoint();
            const auto& end = line->GetEndPoint();
            j["start_point"] = { start.x, start.y, start.z };
            j["end_point"] = { end.x, end.y, end.z };
        }
        break;
    }
    case ObjectType::CUSTOM: { // Cylinder
        const Cylinder* cylinder = dynamic_cast<const Cylinder*>(&obj);
        if (cylinder) {
            j["radius"] = cylinder->GetRadius();
            j["height"] = cylinder->GetHeight();
            j["segments"] = cylinder->GetSegments();
            j["draw_top_base"] = cylinder->GetDrawTopBase();
            j["draw_bottom_base"] = cylinder->GetDrawBottomBase();
        }
        break;
    }
    default:
        break;
    }

    return j;
}

std::unique_ptr<SceneObject> Scene::JsonToSceneObject(const json& j) {
    if (!j.contains("type") || !j.contains("name")) {
        throw std::runtime_error("Invalid object JSON: missing type or name");
    }

    int typeInt = j["type"];
    ObjectType type = static_cast<ObjectType>(typeInt);
    std::string name = j["name"];

    // Odczytaj transformacje
    ImVec3 position(0, 0, 0);
    ImVec3 rotation(0, 0, 0);
    ImVec3 scaleObj(1, 1, 1);

    if (j.contains("position")) {
        auto posArray = j["position"];
        if (posArray.is_array() && posArray.size() == 3) {
            position = ImVec3(posArray[0], posArray[1], posArray[2]);
        }
    }

    if (j.contains("rotation")) {
        auto rotArray = j["rotation"];
        if (rotArray.is_array() && rotArray.size() == 3) {
            rotation = ImVec3(rotArray[0], rotArray[1], rotArray[2]);
        }
    }

    if (j.contains("scale")) {
        auto scaleArray = j["scale"];
        if (scaleArray.is_array() && scaleArray.size() == 3) {
            scaleObj = ImVec3(scaleArray[0], scaleArray[1], scaleArray[2]);
        }
    }

    std::unique_ptr<SceneObject> obj;

    // Utwórz obiekt odpowiedniego typu
    switch (type) {
    case ObjectType::BOX: {
        float size = 1.0f;
        if (j.contains("size")) size = j["size"];
        obj = std::make_unique<Box>(name, position, rotation, scaleObj, size);
        break;
    }
    case ObjectType::SPHERE: {
        float radius = 1.0f;
        int slices = 16;
        int stacks = 12;
        bool wireframe = true;

        if (j.contains("radius")) radius = j["radius"];
        if (j.contains("slices")) slices = j["slices"];
        if (j.contains("stacks")) stacks = j["stacks"];
        if (j.contains("wireframe")) wireframe = j["wireframe"];

        auto sphere = std::make_unique<Sphere>(name, position, rotation, scaleObj, radius);
        sphere->SetSlices(slices);
        sphere->SetStacks(stacks);
        obj = std::move(sphere);
        break;
    }
    case ObjectType::CONE: {
        float radius = 1.0f;
        float height = 2.0f;
        int segments = 16;
        bool drawBase = true;

        if (j.contains("radius")) radius = j["radius"];
        if (j.contains("height")) height = j["height"];
        if (j.contains("segments")) segments = j["segments"];
        if (j.contains("draw_base")) drawBase = j["draw_base"];

        auto cone = std::make_unique<Cone>(name, position, rotation, scaleObj, radius, height);
        cone->SetSegments(segments);
        cone->DrawBase(drawBase);
        obj = std::move(cone);
        break;
    }
    case ObjectType::LINE: {
        ImVec3 startPoint(-0.5f, 0, 0);
        ImVec3 endPoint(0.5f, 0, 0);

        if (j.contains("start_point")) {
            auto startArray = j["start_point"];
            if (startArray.is_array() && startArray.size() == 3) {
                startPoint = ImVec3(startArray[0], startArray[1], startArray[2]);
            }
        }

        if (j.contains("end_point")) {
            auto endArray = j["end_point"];
            if (endArray.is_array() && endArray.size() == 3) {
                endPoint = ImVec3(endArray[0], endArray[1], endArray[2]);
            }
        }

        auto line = std::make_unique<Line>(name, position, rotation, scaleObj, startPoint, endPoint);
        obj = std::move(line);
        break;
    }
    case ObjectType::CUSTOM: { // Cylinder
        float radius = 1.0f;
        float height = 2.0f;
        int segments = 16;
        bool drawTopBase = true;
        bool drawBottomBase = true;

        if (j.contains("radius")) radius = j["radius"];
        if (j.contains("height")) height = j["height"];
        if (j.contains("segments")) segments = j["segments"];
        if (j.contains("draw_top_base")) drawTopBase = j["draw_top_base"];
        if (j.contains("draw_bottom_base")) drawBottomBase = j["draw_bottom_base"];

        auto cylinder = std::make_unique<Cylinder>(name, position, rotation, scaleObj, radius, height);
        cylinder->SetSegments(segments);
        cylinder->DrawTopBase(drawTopBase);
        cylinder->DrawBottomBase(drawBottomBase);
        obj = std::move(cylinder);
        break;
    }
    default:
        throw std::runtime_error("Unknown object type: " + std::to_string(typeInt));
    }

    // Ustaw podstawowe w³aœciwoœci
    if (obj) {
        if (j.contains("visible")) obj->SetVisible(j["visible"]);

        // Ustaw kolory
        if (j.contains("edge_color")) {
            auto color = j["edge_color"];
            if (color.contains("r") && color.contains("g") && color.contains("b") && color.contains("a")) {
                ImColor edgeColor(
                    static_cast<int>(color["r"]),
                    static_cast<int>(color["g"]),
                    static_cast<int>(color["b"]),
                    static_cast<int>(color["a"])
                );
                obj->SetEdgeColor(edgeColor);
            }
        }

        if (j.contains("vertex_color")) {
            auto color = j["vertex_color"];
            if (color.contains("r") && color.contains("g") && color.contains("b") && color.contains("a")) {
                ImColor vertexColor(
                    static_cast<int>(color["r"]),
                    static_cast<int>(color["g"]),
                    static_cast<int>(color["b"]),
                    static_cast<int>(color["a"])
                );
                obj->SetVertexColor(vertexColor);
            }
        }
    }

    return obj;
}
