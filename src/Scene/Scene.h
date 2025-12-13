#pragma once 
#include "PCH.h"
#include "Console.h"
#include "Render.h"
#include "SceneObject.h"
#include <memory>
#include <vector>

class Scene {
    private:
        Console console;
        Renderer3D renderer3D;
        std::vector<std::unique_ptr<SceneObject>> objects; // Przeniesione z Renderera
    
    public:
        Scene();
        void drawScene();

		//na przyszlosc gdyby mialo się przydać getter do renderera
        Renderer3D& GetRenderer() { return renderer3D; }
        const Renderer3D& GetRenderer() const { return renderer3D; }

        void AddObject(std::unique_ptr<SceneObject> object);
        void RemoveObject(unsigned int objectId);
        void ClearObjects();
    
		// Getter obiektów dla Renderera i Registratora
        const std::vector<std::unique_ptr<SceneObject>>& GetObjects() const { return objects; }
        std::vector<std::unique_ptr<SceneObject>>& GetObjects() { return objects; }
};
