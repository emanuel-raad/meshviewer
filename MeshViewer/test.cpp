#include "Importer.h"
#include <string>

int main() {

	std::string path = "nodes.txt";
	std::vector<Point> points;

	importNodes(path, points, Filetype::NODES);
	std::string a;
	std::cin >> a;
}
