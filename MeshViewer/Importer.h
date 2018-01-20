#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>

class Point {
public:
	float x_;
	float y_;
	Point(float x, float y) {
		x_ = x;
		y_ = y;
	}
};

enum class Filetype {
	NODES_2D, NODES_3D, CONNECTIVITY, NORMALS
};

void importNodes(const std::string path, std::vector<glm::vec3>& points, Filetype type) {

	try
	{
		std::cout << "ok1" << std::endl;
		std::string line;
		std::ifstream file(path.c_str());
		while (std::getline(file, line)) {
			std::stringstream stream(line);

			// Add support for more types later
			if (type == Filetype::NODES_2D || type == Filetype::NODES_3D) {
				std::string nodeNumber, xPos, yPos, zPos, nodeID;
				std::getline(stream, nodeNumber, ' ');
				std::getline(stream, xPos, ' ');
				std::getline(stream, yPos, ' ');
				if (type == Filetype::NODES_3D)
					std::getline(stream, zPos, ' ');
				else
					zPos = "0.0";
				std::getline(stream, nodeID, ' ');
				
				std::cout << nodeNumber << ": " << xPos << ", " << yPos << ', ' << zPos << std::endl;
				if (type == Filetype::NODES_2D && ( stoi(nodeID) == 1 || stoi(nodeID) == 3))
					points.push_back(glm::vec3(stof(xPos), stof(yPos), stof(zPos)));
				else if (type == Filetype::NODES_3D)
					points.push_back(glm::vec3(stof(xPos), stof(yPos), stof(zPos)));
			}
		}

	}
	catch (const std::exception& e)
	{
		std::cout << "Problem!" << std::endl;
		std::cout << e.what() << std::endl;
	}

}
