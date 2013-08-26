#include "player.h"
#include "file.h"
#include "draw.h"
#include "events.h"
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
	SDL_Texture* bg = nullptr;
	SDL_Texture* bg2 = nullptr;
	try {
		bg = LoadImage("C:\\Users\\make\\Documents\\bg.png");
		bg2 = LoadImage("C:\\Users\\make\\Documents\\bg2.png");
		title = LoadImage("C:\\Users\\make\\Documents\\title.png");
	}
	catch (const std::runtime_error &e){
        errorToFile(e.what());
		return 4;
    }




	// Game variables
	
	bool quit = false;
	
	int bgX = 0;
	int bg2X = 0;
	
	int gameState = 0;
	
	SDL_Color nofiticationColor = {255, 255, 255};
	textClass notificationText(nofiticationColor);

	notificationText.x = 5;
	notificationText.y = 5;

	rendererClass gameRenderer;

	
	playerClass* playerObject = new playerClass;

	KeyboardHandler keyboard;

	// FPS capper
	Timer frameTimer;
	Timer capTimer;
	std::stringstream capText;
	int countedFrames = 0;

	Animation testanimation("C:\\Users\\make\\Documents\\animtest.png", 4);
	testanimation.x = 50;
	testanimation.y = 50;

	frameTimer.Start();

	while(keyboard.quitPressed == false) {	
		
		capTimer.Start();

		clearScreen();
		// Drawn background
		ApplySurface(bgX,0,bg);
		ApplySurface(bgX + 960 ,0,bg);
		
		ApplySurface(bg2X,0,bg2);
		ApplySurface(bg2X + 960 ,0,bg2);
		bgX -= 2;
		bg2X -= 4;
		
		switch (gameState)
		{
			case 0:
				ApplySurface( 20, 50, title);
				break;
			case 1: 
			{
				gameRenderer.pushIntoRenderQueue(playerObject);
				gameState = 2;
				break;
			}
			case 2:
			{
				std::random_device rng;
				if ((rng() % 1000) == 1) {
					Enemy::enemyType eType = Enemy::DORP;
					gameRenderer.pushIntoRenderQueue(new Enemy(eType));
				}
				
				break;
			}
			default:
				break;
		}
		
		
		//Calculate and correct fps
		float avgFPS = countedFrames / ( frameTimer.getTicks() / 1000.f );
		if( avgFPS > 2000000 )
		{
			avgFPS = 0;
		}
		
		keyboard.handleKeyboardEvents(*playerObject, gameRenderer);

		// Rendering
		testanimation.playAnimation();
		gameRenderer.drawRenderQueue();


		updateScreen();

		if (keyboard.isPressed(SDL_SCANCODE_RETURN) && gameState == 0) {
			gameState = 1;
		}

		

		

		// Background reset if out of bounds
		if(bgX < -960) {
			bgX = 0;
		}
		if(bg2X < -960) {
			bg2X = 0;
		}

		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if( frameTicks < SCREEN_TICK_PER_FRAME )
		{
			//Wait remaining time
			SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
		}

	}

    SDL_Quit();
 
    return 0;
}