#pragma once 
#include "PCH.h"
#include "Console.h"
#include "Render.h"
#include "SceneObject.h"
#include <memory>
#include <vector>
#include <optional>
#include <fstream>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

class Scene {
    private:
        Console console;
        Renderer3D renderer3D;
        std::vector<std::unique_ptr<SceneObject>> objects; // Przeniesione z Renderera
		json SceneObjectToJson(const SceneObject& obj); //funckaj pomocnicza, która konwertuje obiekt sceny do formatu JSON
		std::unique_ptr<SceneObject> JsonToSceneObject(const json& j); //funkcja pomocnicza, która tworzy obiekt sceny z formatu JSON
    
    public:
        Scene();
        void drawScene();

		//na przyszlosc gdyby mialo się przydać getter do renderera
        Renderer3D& GetRenderer() { return renderer3D; }
        const Renderer3D& GetRenderer() const { return renderer3D; }

        void AddObject(std::unique_ptr<SceneObject> object);
        void RemoveObject(unsigned int objectId);
        void MoveObject(unsigned int objectId, ImVec3& newPos);
        void RotateObject(unsigned int objectId, ImVec3& point, ImVec3& newRot);
        void ClearObjects();

        std::optional<unsigned> indexFromId(int id) const;
    
		// Getter obiektów dla Renderera i Registratora
        const std::vector<std::unique_ptr<SceneObject>>& GetObjects() const { return objects; }
        std::vector<std::unique_ptr<SceneObject>>& GetObjects() { return objects; }

        //Zapisywanie i wczytywanie sceny z JSON
        void SaveToFile(const std::string& filename = "scene.json");
        void LoadFromFile(const std::string& filename = "scene.json");
};
