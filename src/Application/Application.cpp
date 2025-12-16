#include "Application.h"
#include "Box.h"
#include "Line.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"

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

    auto box = std::make_unique<Box>("Test Box", 2.0f);
    box->SetPosition(ImVec3(0, 0, 0));
    box->SetEdgeColor(ImColor(255, 0, 0, 255));
    box->reloadCommandRecord();
    scene.AddObject(std::move(box));

	auto sphere = std::make_unique<Sphere>("Test Sphere", 1.0f);
	sphere->SetPosition(ImVec3(3, 0, 0));
	sphere->SetEdgeColor(ImColor(0, 0, 255, 255));
    sphere->reloadCommandRecord();
	scene.AddObject(std::move(sphere));

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