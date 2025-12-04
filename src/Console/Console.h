#pragma once 

#include "PCH.h"

class Console {

	private:
		const char* NAME;
		std::string m_Buffer;

		ImGuiInputTextFlags inputTextFlags;

		 std::vector<std::string> history;
		 size_t currentHistory;

	public:
		Console();
		void Draw();
		int serviceTextInputData(ImGuiInputTextCallbackData* data);
		static int TextCallbackStub(ImGuiInputTextCallbackData* data);
};