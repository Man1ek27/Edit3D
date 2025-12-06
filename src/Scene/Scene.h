#pragma once 
#include "PCH.h"
#include "Console.h"
#include "Render.h"
#include "SceneObject.h"

class Scene {
    private:
        Console console;
        Renderer3D renderer3D;
    
    public:
        void drawScene();
    
        // Metoda do dodawania obiektów
        void AddObject(std::unique_ptr<SceneObject> object);
};
