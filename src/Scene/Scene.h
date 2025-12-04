#pragma once 
#include "PCH.h"
#include "Console.h"
#include "Render.h"

class Scene {
	private:
		Console console;

		Renderer3D renderer3D; // Dodany renderer 3D
		
		std::vector<SceneObject*> objects; //to bedzie pojemnik na wszystkie obiekty które w têtli foreach bêdziemy rysowaæ póŸniej 
		// a ¿e po SceneObject bedzie dziwdziczy³ kazdy objekt to przejedziemy tylko jedn¹ pêtl¹ po tym i dal ka¿dego obiektu wywo³a .Draw() - ka¿dy obiek musi mieæ t¹ metodê o tej samej nazwie - Maniek


	public:
		void drawScene();

};