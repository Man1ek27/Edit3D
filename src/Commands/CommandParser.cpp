#include "CommandParser.h"
#include "Scene.h"

CommandParser::CommandParser(Scene& scene): scene(scene){}


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



std::string CommandParser::parse(std::string& fullCommand) {
	std::stringstream ss(fullCommand);
	std::string argsPart;


	std::string commandStr;
	if (!(ss >> commandStr)) {
		return "";
	}
	command = stringToEnum(commandStr);



	std::getline(ss, argsPart);
	switch (command) {
		case SET_LINE_COLOR: {
			// Format: (R,G,B)
			const std::string regex_wzorzec = R"(\s*\(\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*\)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: SET_LINE_COLOR (R,G,B)";
			}
			else {
				args.push_back(std::stoi(dopasowania[1].str()));
				args.push_back(std::stoi(dopasowania[2].str()));
				args.push_back(std::stoi(dopasowania[3].str()));
				return "";
			}

			break;
		}
		case LINE: {
			// Format: (x1,y1,z1),(x2,y2,z2)
			const std::string regex_wzorzec = R"(\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*,\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: LINE (x1,y1,z1),(x2,y2,z2)";
			}
			else {
				 args.push_back(std::stof(dopasowania[1].str()));
				 args.push_back(std::stof(dopasowania[2].str()));
				 args.push_back(std::stof(dopasowania[3].str()));
				 args.push_back(std::stof(dopasowania[4].str()));
				 args.push_back(std::stof(dopasowania[5].str()));
				 args.push_back(std::stof(dopasowania[6].str()));
				 
				return "";
			}

			break;
		}
		case BOX: {
			// Format: (x1,y1,z1),(x2,y2,z2)
			const std::string regex_wzorzec = R"(\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*,\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: BOX (x1,y1,z1),(x2,y2,z2)";
			}
			else {
				args.push_back(std::stof(dopasowania[1].str()));
				args.push_back(std::stof(dopasowania[2].str()));
				args.push_back(std::stof(dopasowania[3].str()));
				args.push_back(std::stof(dopasowania[4].str()));
				args.push_back(std::stof(dopasowania[5].str()));
				args.push_back(std::stof(dopasowania[6].str()));

				return "";
			}

			break;
		}
		case SPHERE: {
			// Format: (x,y,z),r,(n,m)
			const std::string regex_wzorzec = R"(\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: SPHERE (x,y,z),r,(n,m)";
			}
			else {
				// x, y, z
				args.push_back(std::stof(dopasowania[1].str()));
				args.push_back(std::stof(dopasowania[2].str()));
				args.push_back(std::stof(dopasowania[3].str()));

				// r
				args.push_back(std::stof(dopasowania[4].str()));

				// n, m
				args.push_back(std::stof(dopasowania[5].str()));
				args.push_back(std::stof(dopasowania[6].str()));

				return "";
			}

			break;
		}
		case CONE: {
			// Format: (x1,y1,z1), r1, (x2,y2,z2), r2, n
			const std::string regex_wzorzec = R"(\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: CONE (x1,y1,z1), r1, (x2,y2,z2), r2, n";
			}
			else {
				// Punkt 1 (x1, y1, z1)
				args.push_back(std::stof(dopasowania[1].str()));
				args.push_back(std::stof(dopasowania[2].str()));
				args.push_back(std::stof(dopasowania[3].str()));

				// Promieñ r1
				args.push_back(std::stof(dopasowania[4].str()));

				// Punkt 2 (x2, y2, z2)
				args.push_back(std::stof(dopasowania[5].str()));
				args.push_back(std::stof(dopasowania[6].str()));
				args.push_back(std::stof(dopasowania[7].str()));

				// Promieñ r2
				args.push_back(std::stof(dopasowania[8].str()));

				// Liczba segmentów n
				args.push_back(std::stof(dopasowania[9].str()));

				return "";
			}

			break;
		}
		case CYLINDER: {
			// Format: (x1,y1,z1),(x2,y2,z2), r, n
			const std::string regex_wzorzec = R"(\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*,\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: CYLINDER (x1,y1,z1),(x2,y2,z2), r, n";
			}
			else {
				// Punkt 1 (x1, y1, z1)
				args.push_back(std::stof(dopasowania[1].str()));
				args.push_back(std::stof(dopasowania[2].str()));
				args.push_back(std::stof(dopasowania[3].str()));

				// Punkt 2 (x2, y2, z2)
				args.push_back(std::stof(dopasowania[4].str()));
				args.push_back(std::stof(dopasowania[5].str()));
				args.push_back(std::stof(dopasowania[6].str()));

				// Promieñ r
				args.push_back(std::stof(dopasowania[7].str()));

				// Parametr n (liczba segmentów)
				args.push_back(std::stof(dopasowania[8].str()));

				return "";
			}

			break;
		}
		case DELETE: {
			// Format: id
			const std::string regex_wzorzec = R"(\s*([0-9]+)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: DELETE id (where id is int >= 0)";
			}
			else {
				args.push_back(std::stoi(dopasowania[1].str()));

				return "";
			}

			break;
		}
		case CLEAR_ALL: {
			// Format: brak argumentów
			const std::string regex_wzorzec = R"(\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: CLEAR_ALL (no arguments)";
			}
			else {
				return "";
			}

			break;
		}
		case MOVE: {
			// Format: id (x,y,z)
			const std::string regex_wzorzec = R"(\s*([0-9]+)\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: MOVE id (x,y,z)";
			}
			else {
				// ID
				args.push_back(std::stoi(dopasowania[1].str()));

				// Wektor przesuniêcia: x
				args.push_back(std::stof(dopasowania[2].str()));

				// Wektor przesuniêcia: y
				args.push_back(std::stof(dopasowania[3].str()));

				// Wektor przesuniêcia: z
				args.push_back(std::stof(dopasowania[4].str()));

				return "";
			}
			break;
		}
		case ROTATE: {
			// Format: id,(x,y,z),(alpha,beta,gamma)
			const std::string regex_wzorzec = R"(\s*([0-9]+)\s*,\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*,\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: ROTATE id,(x,y,z),(alpha,beta,gamma)";
			}
			else {
				// 1. ID obiektu
				args.push_back(std::stoi(dopasowania[1].str()));

				// 2. Punkt (x, y, z)
				args.push_back(std::stof(dopasowania[2].str())); 
				args.push_back(std::stof(dopasowania[3].str())); 
				args.push_back(std::stof(dopasowania[4].str())); // z

				// 3. K¹ty (alpha, beta, gamma)
				args.push_back(std::stof(dopasowania[5].str()));
				args.push_back(std::stof(dopasowania[6].str())); 
				args.push_back(std::stof(dopasowania[7].str()));

				return "";
			}

			break;
		}
		case SAVE: {
			// Format: nazwa_pliku (ci¹g znaków)
			const std::string regex_wzorzec = R"(\s*([a-zA-Z0-9_-]+)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: SAVE filename";
			}
			else {
				filename = dopasowania[1].str();
				return "";
			}

			break;
		}
		case LOAD: {
			// Format: nazwa_pliku (ci¹g znaków)
			const std::string regex_wzorzec = R"(\s*([a-zA-Z0-9_.-]+)\s*)";

			std::regex wzorzec(regex_wzorzec);
			std::smatch dopasowania;

			if (!std::regex_match(argsPart, dopasowania, wzorzec)) {
				return "ERROR: Wrong arguments| -- Correct command call: LOAD filename";
			}
			else {
				filename = dopasowania[1].str();
				return "";
			}

			break;
		}
		case UNKNOWN: {
				return "ERROR: UNKNOWN command: Aviable commands: SET_LINE_COLOR, LINE, BOX, SPHERE, CONE, CYLINDER, DELETE, CLEAR_ALL, MOVE, ROTATE, SAVE, LOAD";
			break;
		}
		default: {
			break;
		}
	}
	
}


CommandParser::commandType CommandParser::stringToEnum(std::string& commandStr){
	static const std::unordered_map<std::string, commandType> comandMap = {
		{"SET_LINE_COLOR" , SET_LINE_COLOR},
		{"LINE" , LINE},
		{"BOX", BOX},
		{"SPHERE" , SPHERE},
		{"CONE", CONE},
		{"CYLINDER", CYLINDER},
		{"DELETE", DELETE},
		{"CLEAR_ALL", CLEAR_ALL},
		{"MOVE", MOVE},
		{"ROTATE", ROTATE},
		{"SAVE", SAVE},
		{"LOAD", LOAD}
	};

	auto it = comandMap.find(commandStr);

	if (it != comandMap.end()) {
		return it->second;
	}

	return UNKNOWN;
}



void CommandParser::execute() {

	switch (command) {
		case SET_LINE_COLOR: {
			if (args.size() >= 3) {
				color = ImColor(args[0], args[1], args[2]);
			}
			break;
		}
		case LINE: {
			if (args.size() >= 6) {
				ImVec3 p1(args[0], args[1], args[2]);
				ImVec3 p2(args[3], args[4], args[5]);

				auto line = std::make_unique<Line>("Line",p1, p2);
				line->SetEdgeColor(color);
				line->reloadCommandRecord();
				scene.AddObject(std::move(line));

				
			}
			break;
		}
		case BOX: {
			if (args.size() >= 6) {
				ImVec3 p1(args[0], args[1], args[2]);
				ImVec3 p2(args[3], args[4], args[5]);

				auto box = std::make_unique<Box>("Box", 2.0f); 
				box->SetEdgeColor(color);
				box->SetPosition(p1);
				box->reloadCommandRecord();
				scene.AddObject(std::move(box));

			}

			break;
		}
		case SPHERE: {
			if (args.size() >= 6) {
				ImVec3 p0(args[0], args[1], args[2]);
				float r = args[3];
				ImVec2 nm(args[4], args[5]);

				//Dodawanie sfery do sceny
				auto sphere = std::make_unique<Sphere>("Sphere", r);
				sphere->SetPosition(p0);
				sphere->SetEdgeColor(color); 
				sphere->SetVertexColor(color); 
				sphere->SetSlices(nm.x);
				sphere->SetStacks(nm.y);

				sphere->reloadCommandRecord();
				scene.AddObject(std::move(sphere));


			}

			break;
		}
		case CONE: {
			if (args.size() >= 9) {
				ImVec3 p1(args[0], args[1], args[2]);
				float r1 = args[3];
				ImVec3 p2(args[4], args[5], args[6]);
				float r2 = args[7];
				float n = args[8];

				// Dodawanie sto¿ka do sceny
				auto cone = std::make_unique<Cone>("Cone", r1, 2.0f);
				cone->SetPosition(p1);
				cone->SetEdgeColor(color); 
				cone->SetVertexColor(color);

				cone->reloadCommandRecord();
				scene.AddObject(std::move(cone));


			}

			break;
		}
		case CYLINDER: {
			if (args.size() >= 8) {
				ImVec3 p1(args[0], args[1], args[2]);
				ImVec3 p2(args[3], args[4], args[5]);
				float r = args[6];
				float n = args[7];

				auto cylinder = std::make_unique<Cylinder>("Przekszta³cony walec", r, 1.5f);
				cylinder->SetPosition(p1);
				cylinder->SetRotation(ImVec3(45, 30, 0)); // Obrót wokó³ X i Y
				cylinder->SetScale(ImVec3(1.5f, 0.8f, 1.5f)); // Sp³aszczenie w osi Y
				cylinder->SetEdgeColor(color); 
				cylinder->reloadCommandRecord();
				scene.AddObject(std::move(cylinder));


			}
			break;
		}
		case DELETE: {
			if (args.size() >= 1) {
				int id = args[0];

				scene.RemoveObject(id);
			}
			break;
		}
		case CLEAR_ALL: {
			scene.ClearObjects();
			break;
		}
		case MOVE: {
			if (args.size() >= 4) {
				int id = args[0];
				ImVec3 p1(args[1], args[2], args[3]);

	

				scene.MoveObject(id, p1);


			}
			break;
		}
		case ROTATE: {
			if (args.size() >= 7) {
				float id = args[0];
				ImVec3 p1(args[1], args[2], args[3]);
				ImVec3 rot(args[4], args[5], args[6]);



				scene.RotateObject(id, p1, rot);
			}
			break;
		}
		case SAVE: {
			if (args.size() >= 1) {
				filename = args[0];
			}
			std::string fullPath = filename + ".json";
			std::transform(fullPath.begin(), fullPath.end(), fullPath.begin(),
				[](unsigned char c) { return std::tolower(c); });

			scene.SaveToFile(fullPath);
			break;
		}
		case LOAD: { 
			if (args.size() >= 1) {
				filename = args[0];
			}
			std::string fullPath = filename + ".json";
			std::transform(fullPath.begin(), fullPath.end(), fullPath.begin(),
				[](unsigned char c) { return std::tolower(c); });

			scene.LoadFromFile(fullPath);
			break;
		}
		case UNKNOWN:
			break;

	}
	args.clear();
	command = UNKNOWN;
}