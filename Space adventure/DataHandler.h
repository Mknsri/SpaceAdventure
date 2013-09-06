#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "unzip.h"

#include <string>
#include <sstream>
#include <fstream>

class DataHandler
{
private: 
	std::string dataFilePath;
	std::string dataFileName;

	std::string dataErrorFile;

public:
	DataHandler(void);
	~DataHandler(void);

	bool openDataFile(std::string filePath);

	bool openFile();
	
	void logErrorToFile(std::ostream &errorMessage);

	bool closeFile();

};


#endif