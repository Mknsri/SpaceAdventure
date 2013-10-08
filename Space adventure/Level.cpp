#include "Level.h"


Level::Level(void)
{
	playerObject = new playerClass;
	levelTimer = new Timer();
	bossObject = new gameObject;

	levelCompleted = false;
	levelStarted = false;
	levelPaused = false;

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

		
		}
		
		// if we reach events, stop assetloading
		if (line == "EVENTS") {
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

	// Initiate player object
	playerObject->newGame();
	
	LEventRuntime = LEvent;

}

bool Level::playLevel(rendererClass &renderer) {

	// Start drawing the player once
	if (levelStarted == false) {
		renderer.pushIntoRenderQueue(playerObject);
		levelStarted = true;
	}

	// Play the backgrounds
	backgroundAnimation->scrollAnimation(backgroundAnimation->LEFT);
	backgroundAnimation2->scrollAnimation(backgroundAnimation2->LEFT);

	// Loop through game-events, and trigger by time code
	// Iterator
	std::vector<LevelEvent*>::iterator it;

	if (!levelPaused) {
		for(it = LEventRuntime.begin(); it != LEventRuntime.end();) {
			if ( (*it)->eventTime < levelTimer->getTicks() ) {
				if ((*it)->eventType != "COMPLETE") {

			
					gameObject* ebin = (*it)->fireEvent();
					if ((*it)->eventType == "MONSTRO") {
						bossObject = ebin;
					}
					renderer.pushIntoRenderQueue(ebin);
					it = LEventRuntime.erase(it);
				}
				else {
					levelCompleted = true;
					it = LEventRuntime.erase(it);
				}
			}
			else
				it++;
		}
	}

	// Random powerup check
	// Start counting once 15 secs has passed of level
	if (levelTimer->getTicks() > 15000) {
		std::random_device rng;
		int randomNumber = rng() % 50000;

		if (randomNumber > 0 && randomNumber < 3) {
			renderer.pushIntoRenderQueue(new PowerUp(PowerUp::HEALTH));
		}
		else if (randomNumber > 4 && randomNumber < 8 ) {
			renderer.pushIntoRenderQueue(new PowerUp(PowerUp::MULTIFIRE));
		}
		else if (randomNumber > 8 && randomNumber < 12) {
			renderer.pushIntoRenderQueue(new PowerUp(PowerUp::TRIAMMO));
		}


	}


	// End check
	if (playerObject->isPlayerAlive() == false || bossObject->health == -100 || levelCompleted == true) {
		levelPaused = true;
		if (bossObject->health == -100) {
			levelCompleted = true;
		}
		return false;
	}
	if (bossObject->health < 1) {
		levelPaused = true;
		return true;
	}
	else {
		return true;
	}

}