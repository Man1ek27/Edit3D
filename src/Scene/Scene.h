#pragma once 
#include "PCH.h"
#include "Console.h"
#include "Render.h"

class Scene {
	private:
		Console console;

		Renderer3D renderer3D; // Dodany renderer 3D
	

	public:
		void drawScene();

};