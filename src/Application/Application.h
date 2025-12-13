#pragma once 

#include "PCH.h"
#include "Scene.h"
#include "Render.h"
#include "Box.h"
#include "Line.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"

class Application {

public:
    Application();
    Application(unsigned int width, unsigned int height, sf::String title = "3DEdit");
    void run();

private:
    void handleEvents();

    const unsigned int WINDOW_WIDTH;
    const unsigned int WINDOW_HEIGHT;
    const sf::String WINDOW_TITLE;
    const unsigned int FRAME_LIMIT = 60;

    sf::RenderWindow main_window;

    Scene scene;
};