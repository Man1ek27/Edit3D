#pragma once 

#include "PCH.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <regex>


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
		CLEAR_ALL,
		MOVE,
		ROTATE,
		SAVE,
		LOAD

	};

	private:
		commandType command = UNKNOWN;
		std::vector<float> args;
		std::string filename;


		commandType stringToEnum(std::string& commandStr);

	public:
		std::string parse(std::string& fullCommand);
		void execute();

		static bool isNumber(const std::string& s);
		
};