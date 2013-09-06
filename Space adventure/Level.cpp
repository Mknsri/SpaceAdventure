#include "Level.h"


Level::Level(void)
{
	levelTimer = new Timer();
}


Level::~Level(void)
{
}

void Level::loadLevel(std::string fileName) {
	std::ifstream levelFile;
	levelFile.open(fileName, std::ios::out);

	bool assetsLoaded = false;

	DataHandler errorfile;
	std::ostringstream errorstream;

	std::string line;
	// Read through the files
	while (std::getline(levelFile,line)) {	

		// Wait for EVENTS-line in levelfile
		std::stringstream assetStream(line);
		std::stringstream eventStream(line);

		// Assetname and event time
		std::string assetToken, eventToken;
		Uint32 eventTime;

		// Loop through assets, token is assetname and path is asset pah
		while(std::getline(assetStream,assetToken,'=') && assetsLoaded == false) {
			std::string path;
			assetStream >> path;

			// Load the asset
			loadAsset(assetToken, path);

			errorfile.logErrorToFile(errorstream << "Token:" << assetToken << " Path:" << path);
		
		}
		
		// if we reach events, stop assetloading
		if (line == "EVENTS") {
			errorfile.logErrorToFile(errorstream << "START EVENTS" << '\n');
			assetsLoaded = true;
		}

		// load events
		while(std::getline(eventStream,eventToken,',') && assetsLoaded == true && eventToken != "EVENTS") {
			std::string eventType;
			int objectY;

			// Turn event time to uint32
			eventTime = atoi(eventToken.c_str());

			// send event information to string
			eventStream >> eventType >> objectY;

			// Send event to eventqueue
			LEvent.push_back(new LevelEvent(objectY, eventTime, eventType));

			errorfile.logErrorToFile(errorstream << "Token:" << eventTime << " Event type:" << eventType << " Object y:" << objectY);
		}
	}


	


}

void Level::loadAsset(std::string assetName, std::string assetPath) {
	
	// Load asset
	if (assetName == "bg") {
		backgroundAnimation = new Animation(assetPath, 1, 0, 24);
		backgroundAnimation->x = 0;
		backgroundAnimation->y = 0;
	}
	else if (assetName == "bg2") {
		backgroundAnimation2 = new Animation(assetPath, 1, 0, 16);
		backgroundAnimation2->x = 0;
		backgroundAnimation2->y = 0;
	}

}



void Level::initLevel() {

	// Start or restart level timer
	if(levelTimer->Started())
		levelTimer->Restart();
	else {
		levelTimer->Start();
	}

}

void Level::playLevel(rendererClass &renderer) {
	
	// Play the backgrounds
	backgroundAnimation->scrollAnimation(backgroundAnimation->LEFT);
	backgroundAnimation2->scrollAnimation(backgroundAnimation2->LEFT);

	// Loop through game-events, and trigger by time code
	// Iterators
	std::vector<LevelEvent*>::iterator it;

	for(it = LEvent.begin(); it != LEvent.end();) {
		// Draw all objects
		if ( (*it)->eventTime < levelTimer->getTicks() ) {
			gameObject* ebin = (*it)->fireEvent();
			renderer.pushIntoRenderQueue(ebin);
			it = LEvent.erase(it);
		}
		else
			it++;

	}
	


}