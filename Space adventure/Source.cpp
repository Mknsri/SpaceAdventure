#include "player.h"
#include "file.h"
#include "draw.h"
#include "bulletClass.h"
#include "rendererClass.h"
#include "textClass.h"
#include "Timer.h"
#include "KeyboardHandler.h"
#include "Enemy.h"
#include "Animation.h"

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

	if (TTF_Init() == -1){
    std::cout << TTF_GetError() << std::endl;
    return 2;
}
	
	const int SCREEN_FPS = 60;
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;


	// Load assets
	SDL_Texture* title = nullptr;
	try {
		title = LoadImage("data\\title.png");
	}
	catch (const std::runtime_error &e){
        errorToFile(e.what());
		return 4;
    }




	// Game variables
	bool quit = false;
	int gameState = 0;
	
	// Game classes
	rendererClass gameRenderer;
	playerClass* playerObject = new playerClass;
	KeyboardHandler keyboard;

	// 2 scrolling backgrounds for parallax effect
	Animation backgroundAnimation("data\\bg.png", 1, 0, 24);
	backgroundAnimation.x = 0;
	backgroundAnimation.y = 0;
	Animation backgroundAnimation2("data\\bg2.png", 1, 0, 16);
	backgroundAnimation2.x = 0;
	backgroundAnimation2.y = 0;

	// FPS capper
	Timer frameTimer;
	Timer capTimer;
	int countedFrames = 0;

	// Start counting frames since game start
	frameTimer.Start();

	// Notification text object
	std::stringstream notificationText;
	textClass notification;
	notification.x = 150;
	notification.y = 150;

	//Debug
	std::stringstream teksti;
	textClass debugtext;
	debugtext.x = 200;
	debugtext.y = 200;

	Animation testi("data\\kalalus_death.png",8);
	testi.x = 5;
	testi.y = 5;

	// end debug

	while(keyboard.quitPressed == false) {	
		
		// Start counting frames since gameloop start
		capTimer.Start();

		// Clear screen
		clearScreen();

		// Drawn background
		backgroundAnimation.scrollAnimation(Animation::LEFT);
		backgroundAnimation2.scrollAnimation(Animation::LEFT);

		// Check gamestates
		switch (gameState)
		{
			// Title screen
			case 0:
				ApplySurface( 20, 50, title);

				// Check if the user presses Enter to start a game
				if(keyboard.isPressed(SDL_SCANCODE_RETURN))
					gameState = 1;
				break;
			// Start new game
			case 1: 
			{
				// Start drawing player
				playerObject->newGame();

				gameRenderer.pushIntoRenderQueue(playerObject);
				playerObject->fireDisabled = false;
				gameState = 2;
				break;
			}
			// Start game
			case 2:
			{
				// TODO: Randomly spawn enemies
				//testi.playAnimationOnce();


				std::random_device rng;
				if ((rng() % 100) == 1) {
					gameRenderer.pushIntoRenderQueue(new Enemy(Enemy::DORP));
				}
				
				if (playerObject->isPlayerAlive() == false) {
					gameState = 3;
				}

				break;
			}
			// Death screen
			case 3:
				// Disable player fire
				playerObject->fireDisabled = true;

				// Set you are dead text
				notificationText.str("");
				notificationText << "You are dead! Play again? ( Y / N )";
				notification.setMessage(notificationText);
				notification.drawObject();

				if(keyboard.isPressed(SDL_SCANCODE_Y)) {
					gameState = 1;
				}
				else if (keyboard.isPressed(SDL_SCANCODE_N)) {
					quit = true;
				}

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
		keyboard.handleKeyboardEvents(*playerObject, gameRenderer);

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