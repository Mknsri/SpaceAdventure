#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "textClass.h"

#include <string>
#include <fstream>
#include <vector>


class HighScore
{
public:
	HighScore(void);
	~HighScore(void);

	textClass* highScoreText;

	std::string highScoreArray[2][10];

	void readHighScoreFile(std::string fileName);
	void displayHighScore();
	void writeHighScoreFile();

};

#endif