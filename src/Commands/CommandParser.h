#pragma once 

#include "PCH.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>


class CommandParser {

	enum commandType{
		UNKNOWN = -1,
		SET_LINE_COLOR,
		LINE,
		BOX,
		SPHERE,
		CONE,
		CYLINDER,
		DELETE,
		CLEAR_ALL
	};

	private:
		std::string command = "";
		std::vector<float> args;


		commandType stringToEnum();

	public:
		void parse(std::string& fullCommand);
		void execute();

		static bool isNumber(const std::string& s);
		
};