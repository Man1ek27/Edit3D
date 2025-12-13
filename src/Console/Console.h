#pragma once 
#include "PCH.h"
#include "CommandParser.h"


class Scene;


class Console {

	private:
		const char* NAME;
		std::string m_Buffer;

		ImGuiInputTextFlags inputTextFlags;

		 std::vector<std::string> history;
		 size_t currentHistory;

		 CommandParser parser;

	public:
		Console(Scene &scen);
		void Draw();
		int serviceTextInputData(ImGuiInputTextCallbackData* data);
		static int TextCallbackStub(ImGuiInputTextCallbackData* data);
};