#include "CommandParser.h"

bool CommandParser::isNumber(const std::string& s) {
	try {
		size_t pos;
		std::stof(s, &pos);
		return pos == s.size();
	}
	catch (...) {
		return false;
	}
}



void CommandParser::parse(std::string& fullCommand) {
	std::stringstream ss(fullCommand);
	std::string word;
	std::string argsPart;
	std::stringstream argsFull;



	ss >> command;
	std::cout << command << std::endl;

	std::getline(ss, argsPart);
	argsPart.erase(std::remove_if(argsPart.begin(), argsPart.end(),
		[](char c) {
			return c == ' ' || c == '(' || c == ')';
		}),
		argsPart.end());
	argsFull.str(argsPart);

	char delimiter = ',';
	while (std::getline(argsFull, word, delimiter)) {
		if (isNumber(word)) {
			args.push_back(std::stof(word));
		}
	}
}


CommandParser::commandType CommandParser::stringToEnum(){
	static const std::unordered_map<std::string, commandType> comandMap = {
		{"SET_LINE_COLOR" , SET_LINE_COLOR},
		{"LINE" , LINE},
		{"BOX", BOX},
		{"SPHERE" , SPHERE},
		{"CONE", CONE},
		{"CYLINDER", CYLINDER},
		{"DELETE", DELETE},
		{"CLEAR_ALL", CLEAR_ALL}
	};

	auto it = comandMap.find(command);

	if (it != comandMap.end()) {
		return it->second;
	}

	return UNKNOWN;
}


// tutaj w ka¿dym case mo¿esz napisaæ tworzenie obiektów - jakoœ tzeba bêdzie to potem odwo³aæ ¿eby te obiektu storowaæ w Scene - mo¿e masz pomys³ 
//TO DO - rysowanie obiektów 
//consola nie jest jeszcze skoñczona - ma trochê niedoci¹gniêæ i b³êdów - pewnie nawet ci siê przytafi¹ - no i chce jeszcze oddaæ ob³sugê b³êdów i podpowiadanie sk³adni jak siê 
//Ÿle wpisze komedê 

void CommandParser::execute() {

	
	switch (this->stringToEnum()) {
		case SET_LINE_COLOR:
			if (args.size() >= 3) {
				ImColor col(args[0], args[1], args[2]);
				std::cout << "R: " << col.Value.x
					<< " G: " << col.Value.y
					<< " B: " << col.Value.z
					<< " A: " << col.Value.w << std::endl;
				}
			break;
		case LINE:
			if (args.size() >= 6) {
				ImVec3 p1(args[0], args[1], args[2]);
				ImVec3 p2(args[3], args[4], args[5]);

				std::cout << "p1(" << p1.x << ", " << p1.y << ", " << p1.z << std::endl;
				std::cout << "p2(" << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
			}
			break;
		case BOX:
			if (args.size() >= 6) {
				ImVec3 p1(args[0], args[1], args[2]);
				ImVec3 p2(args[3], args[4], args[5]);

				std::cout << "p1(" << p1.x << ", " << p1.y << ", " << p1.z << std::endl;
				std::cout << "p2(" << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
			}

			break;
		case SPHERE:
			if (args.size() >= 6) {
				ImVec3 p0(args[0], args[1], args[2]);
				float r = args[3];
				ImVec2 nm(args[4], args[5]);

				std::cout << "p0(" << p0.x << ", " << p0.y << ", " << p0.z << std::endl;
				std::cout << "r: " <<r << std::endl;
				std::cout << "n: " <<nm.x << " m:" << nm.y << std::endl;
			}

			break;
		case CONE:
			if (args.size() >= 9) {
				ImVec3 p1(args[0], args[1], args[2]);
				float r1 = args[3];
				ImVec3 p2(args[4], args[5], args[6]);
				float r2 = args[7];
				float n = args[8];

				std::cout << "p1(" << p1.x << ", " << p1.y << ", " << p1.z << std::endl;
				std::cout << "r1" << r1 << std::endl;
				std::cout << "p2(" << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
				std::cout << "r2: " << r2 << std::endl;
				std::cout << "n: " << n << std::endl;
			}

			break;
		case CYLINDER:
			if (args.size() >= 8) {
				ImVec3 p1(args[0], args[1], args[2]);
				ImVec3 p2(args[3], args[4], args[5]);
				float r = args[6];
				float n = args[7];

				std::cout << "p1(" << p1.x << ", " << p1.y << ", " << p1.z << std::endl;
				std::cout << "p2(" << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
				std::cout << "r1: " << r << std::endl;
				std::cout << "n: " << n << std::endl;
			}
			break;
		case DELETE:
			if (args.size() >= 1) {
				float id = args[0];
				std::cout << "id: " << id << std::endl;
			}
			break;
		case CLEAR_ALL:
			std::cout << "clearing all objects ..." << std::endl;
			break;
		case UNKNOWN:
			std::cout << "ERROR";
			break;

		args.clear();
		command = "";
	}
}