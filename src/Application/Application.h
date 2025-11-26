#pragma once 

#include "PCH.h"
#include "Console.h"

class Application {

public:
	Application();
	Application(unsigned int width, unsigned int height, sf::String title = "3DEdit");
	void run();



private:

	const unsigned int WINDOW_WIDTH;
	const unsigned int WINDOW_HEIGHT;
	const sf::String WINDOW_TITLE;

	const unsigned int FRAME_LIMIT = 60;

	sf::RenderWindow main_window;
	sf::RenderWindow console1;

	Console console;
};
