#pragma once 
#include "PCH.h"
#include "CommandParser.h"


class Scene;


class Console {

	private:
		bool scrollToBottom = 0;
		const char* NAME;
		std::string m_Buffer;

		//zmienna przechowuj¹ca tagi do ImGui::Input
		ImGuiInputTextFlags inputTextFlags;

		 std::vector<std::string> history;
		 size_t currentHistory;

		 CommandParser parser;

	public:
		Console(Scene &scen);

		//tysuje konsole
		void Draw();

		//metoda oblugi consoli
		int serviceTextInputData(ImGuiInputTextCallbackData* data);

		//metoda pomocnicza do wywolania serviceTextInputData
		static int TextCallbackStub(ImGuiInputTextCallbackData* data);
};