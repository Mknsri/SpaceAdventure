#include "HighScore.h"
#include "player.h"
#include "draw.h"
#include "bulletClass.h"
#include "rendererClass.h"
#include "textClass.h"
#include "Timer.h"
#include "KeyboardHandler.h"
#include "Enemy.h"
#include "Animation.h"
#include "DataHandler.h"
#include "Level.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <random>


int main(int argc, char** argv){

	initSDL();
	
	const int SCREEN_FPS = 60;
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

	// Resource handler
	DataHandler gameDataHandler;

	// Load assets
	SDL_Texture* title = nullptr;
	title = LoadImage("data\\title.png");
	


	// Game variables
	bool quit = false;
	int gameState = 0;
	
	// Game classes
	rendererClass gameRenderer;
	KeyboardHandler keyboard;
	HighScore highscore;

	// FPS capper
	Timer frameTimer;
	Timer capTimer;
	int countedFrames = 0;

	// Start counting frames since game start
	frameTimer.Start();

	// Notification text object
	std::stringstream notificationText;
	textClass notification;
	notification.x = 180;
	notification.y = 120;

	//Debug
	std::stringstream teksti;
	textClass debugtext;
	debugtext.x = 200;
	debugtext.y = 200;


	// end debug
	Level level1;
	level1.loadLevel("data\\test.dat");

	
	highscore.readHighScoreFile("data\\score.dat");


	while(keyboard.quitPressed == false && quit == false) {	
		
		// Start counting frames since gameloop start
		capTimer.Start();

		// Clear screen
		clearScreen();


		// Check gamestates
		switch (gameState)
		{
			// Title screen
			case 0:
				ApplySurface( 20, 50, title);

				// Check if the user presses Enter to start a game
				if(keyboard.isPressed(SDL_SCANCODE_RETURN)) {
					gameState = 1;
				}
				break;
			// Start new game
			case 1: 
			{
				// Start level
				level1.initLevel();
				
				gameState = 2;
				break;
			}
			// Start game
			case 2:
			{
				
				if (!level1.playLevel(gameRenderer)) {
					if (level1.levelCompleted == true) {
						gameState = 4;
					}
					else {
						gameState = 3;
					}
				}

				break;
			}
			// Death screen
			case 3:

				// Set you are dead text
				notificationText.str("");
				notificationText << "You are dead! Play again? ( Y / N )";
				notification.setMessage(notificationText);
				notification.drawObject();
				highscore.displayHighScore();

				if(keyboard.isPressed(SDL_SCANCODE_Y)) {
					gameState = 1;
				}
				else if (keyboard.isPressed(SDL_SCANCODE_N)) {
					quit = true;
				}

				break;
			// Level1  complete
			case 4:
				notificationText.str("");
				notificationText << "Level complete! Press enter for level 2 ";
				notification.setMessage(notificationText);
				notification.drawObject();

				if(keyboard.isPressed(SDL_SCANCODE_RETURN)) {
					gameState = 5;
				}
				else if (keyboard.isPressed(SDL_SCANCODE_N)) {
					quit = true;
				}
			// Level 2
			case 5:
				break;
			// Level 2 complete
			case 6:
				break;
			// Level 3
			case 7:
				break;
			// Game complete
			case 8:
				break;

			default:
				break;
		}
		
		//Calculate and correct fps
		float avgFPS = countedFrames / ( frameTimer.getTicks() / 1000.f );
		if( avgFPS > 2000000 )
		{
			avgFPS = 0;
		}
		
		// Handle keyboard for player
		keyboard.handleKeyboardEvents(*level1.playerObject, gameRenderer);

		// Draw all the gameObjects
		gameRenderer.drawRenderQueue();

		// Handle game logic
		gameRenderer.handleLogicQueue();
		
		// Update screen
		updateScreen();
		

		// Add a counted frame
		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if( frameTicks < SCREEN_TICK_PER_FRAME )
		{
			//Wait remaining time
			SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
		}

	}

	// Quit SDL
    SDL_Quit();
 
    return 0;
}