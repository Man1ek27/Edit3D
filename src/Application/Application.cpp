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

        // Dodaj przyk³adowy Box do sceny przez scene
        auto box1 = std::make_unique<Box>("Test Box", 2.0f);
        box1->SetPosition(ImVec3(0, 0, 0));
        scene.AddObject(std::move(box1));


        auto line2 = std::make_unique<Line>("Linia ukoœna",
            ImVec3(-1, -1, -1),
            ImVec3(1, 1, 1));
        line2->SetPosition(ImVec3(0, 2, 0)); // Przesuniêcie ca³ej linii
        line2->SetEdgeColor(ImColor(0, 255, 0, 255)); // Zielona
        scene.AddObject(std::move(line2));

         //Dodawanie sfery do sceny
        auto sphere1 = std::make_unique<Sphere>("Kula 1", 1.5f);
        sphere1->SetPosition(ImVec3(-3, 0, 0));
        sphere1->SetEdgeColor(ImColor(255, 165, 0, 255)); // Pomarañczowa siatka
        sphere1->SetVertexColor(ImColor(255, 100, 0, 255)); // Ciemniejszy pomarañcz
        scene.AddObject(std::move(sphere1));

        // Dodawanie sto¿ka do sceny
        auto cone1 = std::make_unique<Cone>("Sto¿ek 1", 1.0f, 2.0f);
        cone1->SetPosition(ImVec3(0.5, 0, -3));
        cone1->SetEdgeColor(ImColor(255, 100, 100, 255)); // Czerwony
        cone1->SetVertexColor(ImColor(255, 50, 50, 255)); // Ciemniejszy czerwony
        scene.AddObject(std::move(cone1));

        auto cylinder3 = std::make_unique<Cylinder>("Przekszta³cony walec", 0.8f, 1.5f);
        cylinder3->SetPosition(ImVec3(-4, -2, 4));
        cylinder3->SetRotation(ImVec3(45, 30, 0)); // Obrót wokó³ X i Y
        cylinder3->SetScale(ImVec3(1.5f, 0.8f, 1.5f)); // Sp³aszczenie w osi Y
        cylinder3->SetEdgeColor(ImColor(255, 150, 50, 255)); // Pomarañczowy
        scene.AddObject(std::move(cylinder3));


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