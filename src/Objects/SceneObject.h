#pragma once
#include "PCH.h"

class SceneObject : sf::Drawable {
	private:
		static unsigned int currentid; // =0 dziêki temu bêdzie autonumeracja
		unsigned int objectId;

	public:
		SceneObject();
};