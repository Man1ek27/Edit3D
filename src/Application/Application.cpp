#include "Application.h"
#include "Box.h"

Application::Application() : Application(1920, 1280, "Edit3D") {
}

Application::Application(unsigned int width, unsigned int height, sf::String title)
    : WINDOW_WIDTH{ width }, WINDOW_HEIGHT{ height }, WINDOW_TITLE{ title },
    main_window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close) {

    main_window.setFramerateLimit(FRAME_LIMIT);
    
    main_window.setPosition(sf::Vector2i(main_window.getPosition().x, 0.f));
    std::ignore = ImGui::SFML::Init(main_window);
}

void Application::handleEvents() {
    while (const auto event = main_window.pollEvent()) {
        ImGui::SFML::ProcessEvent(main_window, *event);

        if (event->is<sf::Event::Closed>()) {
            main_window.close();
        }
    }
}

void Application::run() {
    sf::Clock deltaClock;

    // Dodaj przyk³adowy Box do sceny przez scene
    auto box1 = std::make_unique<Box>("Test Box", 2.0f);
    box1->SetPosition(ImVec3(0, 0, 0));
    scene.AddObject(std::move(box1));

    // Mo¿esz dodaæ wiêcej obiektów
    auto box2 = std::make_unique<Box>("Another Box", 1.0f);
    box2->SetPosition(ImVec3(2, 0, 0));
    box2->SetEdgeColor(ImColor(0, 255, 0, 255)); // Zielone krawêdzie
    scene.AddObject(std::move(box2));

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