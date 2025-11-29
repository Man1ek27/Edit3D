#include "Application.h"


Application::Application() : Application(1200, 800, "Edit3D") {
}

Application::Application(unsigned int width, unsigned int height, sf::String title)
    : WINDOW_WIDTH{ width }, WINDOW_HEIGHT{ height }, WINDOW_TITLE{ title },
    main_window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), WINDOW_TITLE)/*,
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

void Application::run() {
    sf::Clock deltaClock;

    while (main_window.isOpen()) {
        handleEvents();
        ImGui::SFML::Update(main_window, deltaClock.restart());

        main_window.clear(sf::Color::White);

        // Rysowanie widoku 3D przez dedykowany renderer
        renderer3D.Draw3DView();

        // Panel kontrolny
        ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(700, 50), ImGuiCond_FirstUseEver);

        ImGui::Begin("Kontrola 3D");
        ImGui::SliderFloat("Obrot X", &renderer3D.rotationX, 0.0f, 360.0f);
        ImGui::SliderFloat("Obrot Y", &renderer3D.rotationY, 0.0f, 360.0f);
        ImGui::SliderFloat("Powiekszenie", &renderer3D.zoom, 0.1f, 3.0f);
        if (ImGui::Button("Resetuj widok")) {
            renderer3D.rotationX = 0.0f;
            renderer3D.rotationY = 0.0f;
            renderer3D.zoom = 1.0f;
        }
        ImGui::End();

        console.Draw();

        ImGui::SFML::Render(main_window);
        main_window.display();
    }
    ImGui::SFML::Shutdown();
}