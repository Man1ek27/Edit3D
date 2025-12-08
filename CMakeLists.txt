cmake_minimum_required(VERSION 3.28)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --------------------------------------------------------------
# SFML 3
# --------------------------------------------------------------
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG master # SFML 3 rozwija się na brunchu master
)
FetchContent_MakeAvailable(SFML)

# --------------------------------------------------------------
# ImGui
# --------------------------------------------------------------
FetchContent_Declare(
  IMGUI
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.91.9 # lub inna < 1.92.0
)
FetchContent_MakeAvailable(IMGUI)

# --------------------------------------------------------------
# ImGui-SFML
# --------------------------------------------------------------
FetchContent_Declare(
  IMGUI_SFML
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
  GIT_TAG master
)
# klucz! zapewnij ścieżkę do ImGui
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF) # wymuś brak find_package

FetchContent_MakeAvailable(IMGUI_SFML)

# --------------------------------------------------------------
# Twój program
# --------------------------------------------------------------
add_executable(MyApp src/main.cpp
    src/Application/Application.cpp  
    src/Commands/CommandHistory.cpp  
    src/Commands/CommandParser.cpp  
    src/Console/Console.cpp
    src/Math/Matrix.cpp
    src/Math/ImVec3.cpp
    src/Objects/Box.cpp
    src/Objects/Cone.cpp
    src/Objects/SceneObject.cpp
    src/Objects/Sphere.cpp
    src/Rendering/Camera.cpp
    src/Rendering/Render.cpp
    src/Scene/Scene.cpp
    src/UI/UI.cpp
    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
 "src/Objects/Line.cpp" "src/Objects/Cylinder.cpp")

target_include_directories(MyApp PRIVATE
    ${CMAKE_BINARY_DIR}/_deps/imgui-src
)


target_include_directories(MyApp PRIVATE
    src/
    src/Application
    src/Commands
    src/Math
    src/Objects
    src/Rendering
    src/Scene
    src/UI
    src/Console
    ${imgui_SOURCE_DIR}   # do nagłówków ImGui
    ${imgui_sfml_SOURCE_DIR}  # jeśli będziesz używać bezpośrednich nagłówków ImGui-SFML
    ${imgui_SOURCE_DIR}/misc/cpp
)

target_link_libraries(MyApp PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    ImGui-SFML::ImGui-SFML
)
