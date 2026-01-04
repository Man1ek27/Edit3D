#include "Console.h"
#include "Application.h"


Console::Console(Scene& scen) : NAME{ "Console" }, parser(scen) {
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
				if (!history[currentHistory]._Starts_with("ERROR:")) {
					data->InsertChars(0, history[currentHistory].c_str());
				}
			}
			
		}		
	}
	return 0;
}


void Console::Draw() {
	ImGui::SetNextWindowSize(ImVec2(1620, 160), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(0, 850));
	ImGui::Begin(NAME,  nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	
		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -40), false, ImGuiWindowFlags_HorizontalScrollbar);

			ImGui::SetCursorPosY(160);
			for (std::string& log : history) {

				ImGui::Text(log.c_str());
			}


			if (scrollToBottom) {
				ImGui::SetScrollHereY(1.0f);
				scrollToBottom = false;
			}
		ImGui::EndChild();

		ImGui::SetCursorPosY(120);
		ImGui::AlignTextToFramePadding();
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ">");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-1);
		if (ImGui::InputText("##Input", &m_Buffer, inputTextFlags, &Console::TextCallbackStub, (void*)this)) {
			if (m_Buffer != "") {
				history.push_back(m_Buffer);
				scrollToBottom = true;

				if (!m_Buffer.empty()) {
					currentHistory = history.size();

					std::string call = parser.parse(m_Buffer);
					if ( call != "") {
						history.push_back(call);
					}
					else parser.execute();
				}
				m_Buffer = "";
			}
			ImGui::SetKeyboardFocusHere(-1);
		}
	ImGui::End();
}