#include "HighScore.h"


HighScore::HighScore(void)
{
	highScoreText = new textClass();

	for (int i = 0; i < 10;i++) {
		highScoreArray[0][i] = "Nimi";
		highScoreArray[1][i] = "Score";
	}

	highScoreText->x = 200;
	highScoreText->y = 200;
}


HighScore::~HighScore(void)
{
}

void HighScore::readHighScoreFile(std::string fileName) {

	std::ifstream highScoreFile;
	highScoreFile.open(fileName, std::ios::out);


	std::string line;
	// Read through the files
	int i = 0;
	while (std::getline(highScoreFile,line,'=')) {	
		
		std::stringstream lineStream(line);

		std::string scoreName, scoreValue;
		lineStream >> scoreValue;

		while(std::getline(lineStream,scoreName,'=')) {
			highScoreArray[0][i] = scoreName;
			highScoreArray[1][i] = scoreValue;
		}
		
		lineStream.str("");
		i++;
		

	}

	// Set array
	std::stringstream hiScoreMsg;
	
	for (int i = 0;i < 10;i++) {
		hiScoreMsg << highScoreArray[0][i] << " --- " << highScoreArray[1][i] << std::endl;
		highScoreText->setMessage(hiScoreMsg);
	}
	
}

void HighScore::displayHighScore() {
	
	highScoreText->drawObject();


}