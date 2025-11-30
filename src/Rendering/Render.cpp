#include "Render.h"

Renderer3D::Renderer3D()
    : rotationX(45.0f), rotationY(45.0f), zoom(1.0f), viewportSize(ImVec2(400, 400)),

    // inicjalizacja views
    views{ {
            // Kolejnoœæ i liczba elementów MUSI zgadzaæ siê z rozmiarem 4
            { 90.0f, 0.0f, "Widok Gora" },
            { 0.0f, 90.0f, "Widok Bok" },
            { 0.0f, 0.0f, "Widok Przod" },
            { rotationX, rotationY, "Widok Perspektywa" }
          } } {


    // Inicjalizacja wierzcho³ków szeœcianu
    cubeVertices = {
        {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, // tylna œciana
        {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}      // przednia œciana
    };

    // Definicja krawêdzi szeœcianu (po³¹czenia miêdzy wierzcho³kami)
    cubeEdges = {
        {0,1}, {1,2}, {2,3}, {3,0}, // tylna œciana
        {4,5}, {5,6}, {6,7}, {7,4}, // przednia œciana
        {0,4}, {1,5}, {2,6}, {3,7}  // po³¹czenia miêdzy œcianami
    };


    
}

// Funkcja do rzutowania 3D na 2D
ImVec2 Renderer3D::project3DTo2D(const ImVec3& point, const ImVec2& center, float scale) {
    // Proste rzutowanie perspektywiczne
    float factor = 2.0f / (2.0f + point.z * zoom);
    float x = point.x * factor * scale;
    float y = point.y * factor * scale;

    return ImVec2(center.x + x, center.y - y); // Oœ Y jest odwrócona w oknie
}

 //Funkcja do obracania punktu 3D
ImVec3 Renderer3D::rotatePoint(const ImVec3& point, float rotX, float rotY) {
    // Konwersja stopni na radiany
    float radX = rotX * 3.14159f / 180.0f;
    float radY = rotY * 3.14159f / 180.0f;

    // Obroty
    float cosX = std::cos(radX);
    float sinX = std::sin(radX);
    float cosY = std::cos(radY);
    float sinY = std::sin(radY);

    // Obrot wokó³ osi Y
    float x1 = point.x * cosY - point.z * sinY;
    float z1 = point.x * sinY + point.z * cosY;
    float y1 = point.y;

    // Obrot wokó³ osi X
    float y2 = y1 * cosX - z1 * sinX;
    float z2 = y1 * sinX + z1 * cosX;

    return ImVec3(x1, y2, z2);
}

void Renderer3D::handleViewportInteraction() {
    //INFO: Funkcja zwi¹zana z ruszaniem myszk¹ i zoomowaniem za pomoc¹ myszki.

    if (ImGui::IsWindowHovered()) {
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
            ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
            rotationY += delta.x * 0.5f;
            rotationX += delta.y * 0.5f;
            ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);
        }

        float wheel = ImGui::GetIO().MouseWheel;
        if (wheel != 0) {
            zoom += wheel * 0.1f;
            zoom = std::max(0.1f, std::min(zoom, 3.0f));
        }
    }
}


//poprawone drawCube rotX i rotY to rotacje dla poszczególnych view
void Renderer3D::drawCube(float rotX, float rotY) {
    ImVec2 viewportPos = ImGui::GetCursorScreenPos();
    ImVec2 center(viewportPos.x + viewportSize.x * 0.5f, viewportPos.y + viewportSize.y * 0.5f);
    float scale = std::min(viewportSize.x, viewportSize.y) * 0.2f;


	//COMMENT, INFO: TO JEST NAJWAZNIEJSZE. Imgui posiada wbudowany system rysowania, uzyskujemy do niego dostêp w draw_list.
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
	//wystarczy teraz dodaæ do niego elementy rysunkowe, a imgui zajmie siê reszt¹.
	//Na tyle na ile rozumiem (a mogê byæ w b³êdzie) to imgui w ka¿dej klatce automatycznie rysuje wszystko od nowa.
    //Niestety, narazie z tego co widzê to ka¿dy viewport (czyli okno imgui) posiada swój w³asny draw_list
    // (mo¿e jest copy constructor, wiêc wystarczy³oby draw_list skopiowac - nie wiem)
	//wiêc nie wiem jak bêdzie z koncepcj¹ "generuj i obracaj raz, a potem tylko renderuj"  - jeszcze siê przyjrzê.
	//Prawdopodobnie dostêp do generowanych i obracanych obiektów bardziej globalny, a renderowanie w ka¿dym oknie osobno.

    // T³o viewportu
    draw_list->AddRectFilled(viewportPos,
        ImVec2(viewportPos.x + viewportSize.x, viewportPos.y + viewportSize.y),
        IM_COL32(20, 10, 10, 255));

    // Obracanie i rzutowanie wierzcho³ków
    std::vector<ImVec2> projectedVertices;
    for (const auto& vertex : cubeVertices) {
        ImVec3 rotated = rotatePoint(vertex, rotX, rotY);   // zmienione na przekazywane - Maniek
        projectedVertices.push_back(project3DTo2D(rotated, center, scale));
    }

    // Rysowanie krawêdzi szeœcianu
    for (const auto& edge : cubeEdges) {
        draw_list->AddLine(projectedVertices[edge.x],
            projectedVertices[edge.y],
            IM_COL32(20, 15, 55, 255), 2.0f);
    }

    // Rysowanie wierzcho³ków
    for (const auto& vertex : projectedVertices) {
        draw_list->AddCircleFilled(vertex, 3.0f, IM_COL32(255, 0, 0, 255));
    }
}

void Renderer3D::Draw3DView() {
    ImGui::SetNextWindowSize(ImVec2(1200, 850), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    //ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::Begin("Widok 3D", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	    //DEBUG: Informacja o widocznoœci okna
        ImGui::Text("RotationX: %.2f, RotationY: %.2f", rotationX, rotationY);


        //viewportSize = ImGui::GetContentRegionAvail();

        
        //Ryzowanie poszczególnych view
        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0) {
                //Margin LEFT
                ImGui::SetCursorPosX(ImGui::GetCursorStartPos().x + 150);
            }
            ImGui::BeginChild(views[i].name.c_str(), viewportSize, true, ImGuiWindowFlags_NoScrollbar );
            ImGui::Text("** %s **", views[i].name.c_str());
            ImGui::Text("** %f - %f **", views[i].rotX, views[i].rotY);
            ImGui::Separator();


            if (i == 3) {
                views[i].rotX = rotationX;
                views[i].rotY = rotationY;

                // Obs³uga interakcji tylko dla perspective
                handleViewportInteraction();
            }
            //Wywo³anie odpowiedniego rysowania cube
            drawCube(views[i].rotX, views[i].rotY);

            ImGui::EndChild();

            if (i % 2 == 0) {
                ImGui::SameLine();
            }


        }

        // Rysowanie szeœcianu
        //drawCube();

        // Obs³uga interakcji
        //handleViewportInteraction();
        
    ImGui::End();
}