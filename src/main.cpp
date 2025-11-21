#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "ImGui + SFML");
    sf::Clock deltaClock;

    window.setFramerateLimit(60);
    std::ignore = ImGui::SFML::Init(window);

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Test window");
        ImGui::Button("Guzik 1", ImVec2(60, 50));
        ImGui::SameLine();
        ImGui::Button("Guzik 2 :-D");
        ImGui::Button("Guzik 3 :-(");

        ImGui::Button("Guzik 4", ImVec2(60, 50));
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Button("Guzik 5 :-D");
        ImGui::Button("Guzik 6 :-)");
        ImGui::EndGroup();
        ImGui::End();

        window.clear();
        std::cout << "dzia³a" << std::endl;
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}