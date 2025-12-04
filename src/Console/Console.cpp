#include "Console.h"
#include "Application.h"


Console::Console() : NAME{ "Console" } {
	inputTextFlags = 
		ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackCompletion |
		ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackAlways | ImGuiInputTextFlags_CharsUppercase;
	currentHistory = history.size() - 1;
}

int Console::TextCallbackStub(ImGuiInputTextCallbackData* data){
	Console* console = (Console*)data->UserData;
	return console->serviceTextInputData(data);
}

int Console::serviceTextInputData(ImGuiInputTextCallbackData* data) {
	if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory) {
		if (history.empty()) return 0;

		const int prev_history_pos = currentHistory;

		if (data->EventKey == ImGuiKey_UpArrow) {
			if (currentHistory == -1) {
				currentHistory = history.size() - 1;
			}
			else if (currentHistory > 0) {
				currentHistory--;
			}
			std::cout << "up" << std::endl;
			
		}
		else if (data->EventKey == ImGuiKey_DownArrow) {
			if (currentHistory != -1) {
				if (++currentHistory >= history.size()) {
					currentHistory = -1;
				}
			}
			
		}

		if (currentHistory != prev_history_pos) {
			data->DeleteChars(0, data->BufTextLen);

			if (currentHistory != -1) {
				data->InsertChars(0, history[currentHistory].c_str());
			}
			
		}		
	}
	return 0;
}


void Console::Draw() {
	ImGui::SetNextWindowSize(ImVec2(1620, 160), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(0, 850));
	ImGui::Begin(NAME,  nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	
		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -70), false, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::Text("Log 1...");
			ImGui::Text("Log 2...");
			ImGui::Text("Log 1...");
			ImGui::Text("Log 2...");
			ImGui::Text("Log 2...");
			ImGui::Text("Log 2...");

			//if (scrollToBottom) {
				ImGui::SetScrollHereY(1.0f);
				//scrollToBottom = false
			//}
		ImGui::EndChild();

		ImGui::SetCursorPosY(90);
		ImGui::SetNextItemWidth(-1);
		if (ImGui::InputText("##Input", &m_Buffer, inputTextFlags, &Console::TextCallbackStub, (void*)this)) {
			std::cout << m_Buffer << std::endl;	
			history.push_back(m_Buffer);
			m_Buffer = "";
			ImGui::SetKeyboardFocusHere(-1);
		}
	ImGui::End();
}