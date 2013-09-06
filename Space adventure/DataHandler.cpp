#include "DataHandler.h"


DataHandler::DataHandler(void)
{

	// Default path and filenames
	dataFilePath = "data\\";
	dataFileName = dataFilePath + "gamedata.pkt";
	dataErrorFile = dataFilePath + "errorlog.txt";

}


DataHandler::~DataHandler(void)
{
}

bool DataHandler::openDataFile(std::string filePath) {
	return true;
}

void DataHandler::logErrorToFile(std::ostream &errorMessage) {	

	std::ofstream myfile;
	std::ostringstream& s = dynamic_cast<std::ostringstream&>(errorMessage);
	
	myfile.open (dataErrorFile, std::ios::out | std::ios::app);
	myfile << s.str() << std::endl;
	myfile.close();

	// Clear the stream
	s.str("");
	s.flush();
	errorMessage.flush();
}
