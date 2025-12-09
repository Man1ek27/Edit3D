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

	// Przyk³ady dodawania Boxów
    //{
        // Dodaj przyk³adowy Box do sceny przez scene
        auto box1 = std::make_unique<Box>("Test Box", 2.0f);
        box1->SetPosition(ImVec3(0, 0, 0));
        scene.AddObject(std::move(box1));

    //    // Mo¿esz dodaæ wiêcej obiektów
    //    auto box2 = std::make_unique<Box>("Another Box", 1.0f);
    //    box2->SetPosition(ImVec3(2, 0, 0));
    //    box2->SetEdgeColor(ImColor(0, 255, 0, 255)); // Zielone krawêdzie
    //    scene.AddObject(std::move(box2));
    //}

	// Przyk³ad dodania linii
    //{
    //    auto line1 = std::make_unique<Line>("Linia 1");
    //    line1->SetStartPoint(ImVec3(-2, 0, 0));
    //    line1->SetEndPoint(ImVec3(2, 0, 0));
    //    line1->SetEdgeColor(ImColor(255, 0, 255, 255)); // Magenta
    //    line1->SetVertexColor(ImColor(0, 255, 255, 255)); // Cyjan
    //    scene.AddObject(std::move(line1));

        //// Inny przyk³ad
        auto line2 = std::make_unique<Line>("Linia ukoœna",
            ImVec3(-1, -1, -1),
            ImVec3(1, 1, 1));
        line2->SetPosition(ImVec3(0, 2, 0)); // Przesuniêcie ca³ej linii
        line2->SetEdgeColor(ImColor(0, 255, 0, 255)); // Zielona
        scene.AddObject(std::move(line2));

    //    // Linia z transformacj¹
    //    auto line3 = std::make_unique<Line>("Linia transformowana");
    //    line3->SetStartPoint(ImVec3(0, 0, 0));
    //    line3->SetEndPoint(ImVec3(1, 0, 0)); // Linia o d³ugoœci 1 wzd³u¿ osi X
    //    line3->SetPosition(ImVec3(0, -2, 0));
    //    line3->SetRotation(ImVec3(0, 45, 0)); // Obrót 45 stopni wokó³ Y
    //    line3->SetScale(ImVec3(20, 10000000, 100000)); // Podwójna d³ugoœæ -  INFO : ZWROCCIE UWAGE, ¯e skalujemy tylko w osi X, aby linia pozosta³a lini¹
    //    scene.AddObject(std::move(line3));
    //}


	//Przyk³ady dodawania sfer
    {
         //Dodawanie sfery do sceny
        auto sphere1 = std::make_unique<Sphere>("Kula 1", 1.5f);
        sphere1->SetPosition(ImVec3(-3, 0, 0));
        sphere1->SetEdgeColor(ImColor(255, 165, 0, 255)); // Pomarañczowa siatka
        sphere1->SetVertexColor(ImColor(255, 100, 0, 255)); // Ciemniejszy pomarañcz
        scene.AddObject(std::move(sphere1));

        //// Sfera z wiêksz¹ liczb¹ segmentów (g³adsza)t
        //auto sphere2 = std::make_unique<Sphere>("G³adka kula", 1.0f);
        //sphere2->SetPosition(ImVec3(1, 1, 1));
        //sphere2->SetSlices(32);   // Wiêcej segmentów w poziomie
        //sphere2->SetStacks(24);   // Wiêcej segmentów w pionie
        //sphere2->SetEdgeColor(ImColor(0, 200, 255, 255)); // Jasnoniebieski
        //scene.AddObject(std::move(sphere2));

        // Sfera z transformacj¹
    //    auto sphere3 = std::make_unique<Sphere>("Sp³aszczona kula", 1.0f);
    //    sphere3->SetPosition(ImVec3(3, -2, 0));
    //    sphere3->SetScale(ImVec3(1.5f, 0.7f, 1.5f)); // Sp³aszczenie w osi Y
    //    sphere3->SetRotation(ImVec3(0, 30, 0)); // Obrót 30 stopni wokó³ Y
    //    sphere3->SetEdgeColor(ImColor(150, 0, 255, 255)); // Fioletowy
    //    scene.AddObject(std::move(sphere3));
    }

	//Przyk³ady dodawania sto¿ków
    {
        // Dodawanie sto¿ka do sceny
        auto cone1 = std::make_unique<Cone>("Sto¿ek 1", 1.0f, 2.0f);
        cone1->SetPosition(ImVec3(0.5, 0, -3));
        cone1->SetEdgeColor(ImColor(255, 100, 100, 255)); // Czerwony
        cone1->SetVertexColor(ImColor(255, 50, 50, 255)); // Ciemniejszy czerwony
        scene.AddObject(std::move(cone1));

        // Sto¿ek z wiêksz¹ liczb¹ segmentów (g³adsza podstawa)
        //auto cone2 = std::make_unique<Cone>("G³adki sto¿ek", 1.2f, 2.5f);
        //cone2->SetPosition(ImVec3(0, 2, 0));
        //cone2->SetSegments(32); // Wiêcej segmentów = g³adsza podstawa
        //cone2->SetEdgeColor(ImColor(100, 255, 100, 255)); // Zielony
        //scene.AddObject(std::move(cone2));

        // Sto¿ek z transformacj¹ (obrót i skala)
        //auto cone3 = std::make_unique<Cone>("Przekszta³cony sto¿ek", 0.8f, 1.5f);
        //cone3->SetPosition(ImVec3(-3, -2, 0));
        //cone3->SetRotation(ImVec3(45, 0, 0)); // Obrót 45 stopni wokó³ X
        //cone3->SetScale(ImVec3(1.0f, 2.0f, 1.0f)); // Wyd³u¿enie w osi Y
        //cone3->DrawBase(false); // Bez podstawy
        //cone3->SetEdgeColor(ImColor(100, 100, 255, 255)); // Niebieski
        //scene.AddObject(std::move(cone3));
    }

    {
        // Dodawanie walca do sceny
        //auto cylinder1 = std::make_unique<Cylinder>("Walec 1", 1.0f, 2.0f);
        //cylinder1->SetPosition(ImVec3(4, 0, 4));
        //cylinder1->SetEdgeColor(ImColor(200, 100, 200, 255)); // Fioletowy
        //cylinder1->SetVertexColor(ImColor(150, 50, 150, 255)); // Ciemniejszy fiolet
        //scene.AddObject(std::move(cylinder1));

        //// Walec z wiêksz¹ liczb¹ segmentów (g³adsza podstawa)
        //auto cylinder2 = std::make_unique<Cylinder>("G³adki walec", 1.2f, 2.5f);
        //cylinder2->SetPosition(ImVec3(0, 3, 0));
        //cylinder2->SetSegments(32); // Wiêcej segmentów = g³adsza podstawa
        //cylinder2->SetEdgeColor(ImColor(100, 200, 255, 255)); // Jasnoniebieski
        //scene.AddObject(std::move(cylinder2));

        //// Walec z transformacj¹ (obrót i skala)
        auto cylinder3 = std::make_unique<Cylinder>("Przekszta³cony walec", 0.8f, 1.5f);
        cylinder3->SetPosition(ImVec3(-4, -2, 4));
        cylinder3->SetRotation(ImVec3(45, 30, 0)); // Obrót wokó³ X i Y
        cylinder3->SetScale(ImVec3(1.5f, 0.8f, 1.5f)); // Sp³aszczenie w osi Y
        cylinder3->SetEdgeColor(ImColor(255, 150, 50, 255)); // Pomarañczowy
        scene.AddObject(std::move(cylinder3));

        //// Walec bez jednej podstawy
        //auto cylinder4 = std::make_unique<Cylinder>("Walec bez górnej podstawy", 1.0f, 2.0f);
        //cylinder4->SetPosition(ImVec3(-2, -3, 0));
        //cylinder4->DrawTopBase(false); // Bez górnej podstawy
        //cylinder4->SetEdgeColor(ImColor(50, 200, 100, 255)); // Zielony
        //scene.AddObject(std::move(cylinder4));

        //// Walec odwrócony
        //auto cylinder5 = std::make_unique<Cylinder>("Odwrócony walec", 1.0f, 2.0f);
        //cylinder5->SetPosition(ImVec3(2, -3, 0));
        //cylinder5->SetRotation(ImVec3(0, 0, 90)); // Obrót 90 stopni wokó³ Z
        //cylinder5->SetEdgeColor(ImColor(255, 100, 100, 255)); // Czerwony
        //scene.AddObject(std::move(cylinder5));



    }

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