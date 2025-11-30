#include "Application.h"


Application::Application() : Application(1920, 1280, "Edit3D") {
}

Application::Application(unsigned int width, unsigned int height, sf::String title)
    : WINDOW_WIDTH{ width }, WINDOW_HEIGHT{ height }, WINDOW_TITLE{ title },
    main_window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close)/*,
    console_window(sf::VideoMode({ 1200, 200 }), "Consola")*/ {
        //COMMENT: wyrzuci³em console_window bo nie jest narazie potrzebne

    main_window.setFramerateLimit(FRAME_LIMIT);
    std::ignore = ImGui::SFML::Init(main_window);
    //std::ignore = ImGui::SFML::Init(console_window);
	//COMMENT: wyrzuci³em console_window bo nie jest narazie potrzebne
}

void Application::handleEvents() {
    while (const auto event = main_window.pollEvent()) {
        ImGui::SFML::ProcessEvent(main_window, *event);

        if (event->is<sf::Event::Closed>()) {
            main_window.close();
        }
    }
}

void Application::run() { // nominalnie w Application nie chcemy "suchego kodu" tylko ¿eby by³o tworzenie instancji obiektów i wywo³anie ich metod - Maniek
    sf::Clock deltaClock;

    while (main_window.isOpen()) {
        handleEvents();
        ImGui::SFML::Update(main_window, deltaClock.restart());

        main_window.clear(sf::Color::White);

        scene.drawScene();

        ImGui::SFML::Render(main_window);
        main_window.display();
    }
    ImGui::SFML::Shutdown();
}


