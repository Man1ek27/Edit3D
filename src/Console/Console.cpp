#include "Console.h"
#include "Application.h"


Console::Console() : NAME{ "Console" } {
}

void Console::Draw() {
	ImGui::SetNextWindowSize(ImVec2(1620, 160), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(0, 850));
	ImGui::Begin(NAME,  nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		
	ImGui::End();
}