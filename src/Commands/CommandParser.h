#pragma once 

#include "PCH.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <regex>
#include <format>

#include "Box.h"
#include "Line.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"

class Scene;

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
		ImColor color = { 0,0,0 };
		Scene& scene;



		commandType stringToEnum(std::string& commandStr);

	public:
		CommandParser(Scene& scene);
		std::string parse(std::string& fullCommand);
		void execute();

		static bool isNumber(const std::string& s);
		
};