#include "Application.h"

Application::Application(): Application(1200, 800, "Edit3D") {
}

Application::Application(unsigned int width, unsigned int height, sf::String title) 
	:WINDOW_WIDTH{ width }, WINDOW_HEIGHT{ height }, WINDOW_TITLE{ title }, main_window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), WINDOW_TITLE), console1(sf::VideoMode({ 1200, 200 }),"Consola") {

	main_window.setFramerateLimit(FRAME_LIMIT);
	main_window.clear(sf::Color::White);
	std::ignore = ImGui::SFML::Init(main_window);
	std::ignore = ImGui::SFML::Init(console1); // to tylko testowo raczej i tak najlepiej kosolê robiæ w nowym oknie ImGUI 
}


void Application::run() {
	sf::Clock deltaClock;

	while (main_window.isOpen()) {
		while (const auto event = main_window.pollEvent()) {
			ImGui::SFML::ProcessEvent(main_window, *event);
			if (event->is<sf::Event::Closed>()) main_window.close();
		}
		ImGui::SFML::Update(main_window, deltaClock.restart());

		console.Draw();

		main_window.clear(sf::Color::White);
		ImGui::SFML::Render(main_window);
		main_window.display();



	}
	ImGui::SFML::Shutdown();
}