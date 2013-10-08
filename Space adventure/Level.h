#ifndef LEVEL_H
#define LEVEL_H

#include "DataHandler.h"
#include "player.h"
#include "gameObject.h"
#include "Enemy.h"
#include "Animation.h"
#include "Timer.h"
#include "rendererClass.h"
#include "LevelEvent.h"

#include <fstream>
#include <iostream>
#include <string>
#include <random>


class Level
{
	
	public:
		// Levelname
		std::string levelName;

		// Timer based events
		Timer* levelTimer;

		// Event vector, loaded at init
		// And looped while playing
		std::vector<LevelEvent *> LEventRuntime;

		// Original vector
		std::vector<LevelEvent *> LEvent;

		bool levelStarted;
		bool levelCompleted;
		bool levelPaused;

		// 2 animations for parallax effect
		Animation* backgroundAnimation;
		Animation* backgroundAnimation2;

		Level(void);
		~Level(void);

		// Init level parameters
		void initLevel();

		// Load asset by identifier
		void loadAsset(std::string assetName, std::string assetPath);
		
		// Load level resources from file
		void loadLevel(std::string fileName);

		// Loop level - manipulates renderer
		bool playLevel(rendererClass &renderer);

		// Player object
		playerClass* playerObject;
		gameObject* bossObject;

};

#endif

