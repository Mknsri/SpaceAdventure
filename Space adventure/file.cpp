#include "file.h"


int errorToFile(std::string msg) {
	std::ofstream myfile;
	myfile.open ("data\\debug.txt", std::ios::out | std::ios::app);
	myfile << msg << "\n";
	myfile.close();

	return 0;
}
