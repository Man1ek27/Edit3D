#pragma once 
#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//Rendering stuff
#include <vector>
#include <utility>
#include <cmath>

//COMMENT: IMGUI nie ma ImVec3, ale w ka¿dym projekcie jaki przejrza³em na githubie ludzie implementuj¹ swoj¹ wersjê,
//wiêc wierzê ¿e nie sprawi to (mam nadziejê) za duzo problemów.
struct ImVec3 {
    float x, y, z;
    ImVec3() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
    ImVec3(float _x, float _y, float _z) noexcept : x(_x), y(_y), z(_z) {}
};
