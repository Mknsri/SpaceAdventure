#include "KeyboardHandler.h"

// Init quit as false
KeyboardHandler::KeyboardHandler(void)
{
		quitPressed = false;
}


KeyboardHandler::~KeyboardHandler(void)
{
}

// Handle events from keyboard
void KeyboardHandler::handleKeyboardEvents(playerClass& playerObj, rendererClass &renderer) {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)	{
			quitPressed = true;
		}
		else if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_RETURN:
				break;
				case SDLK_SPACE:
					// Only allows player to fire once per keypress
					if (!playerObj.fireDisabled) {
						playerObj.playerFire();

						// Create a bullet and push it into the rendererqueue
						renderer.pushIntoRenderQueue(new bulletClass(playerObj.x, playerObj.y));
						playerObj.fireDisabled = true;
					}
				break;
				// Player controls
				case SDLK_UP:
					playerObj.yVelocity = -1;
				break;
				case SDLK_DOWN:
					playerObj.yVelocity = 1;
				break;
				case SDLK_LEFT:
					playerObj.xVelocity = -1;
				break;
				case SDLK_RIGHT:
					playerObj.xVelocity = 1;
				break;

				// Player quits game
				case SDLK_ESCAPE:
					quitPressed = true;
				break;

				// Spawns enemy, for debug
				case SDLK_e:
				{
					Enemy::enemyType eType = Enemy::DORP;
					renderer.pushIntoRenderQueue(new Enemy(eType));
					break;
				}
				default:
				break;
			}
		}

		//Keyup events
		else if(event.type == SDL_KEYUP ){
			switch(event.key.keysym.sym) {

					// Allows player to fire again
					case SDLK_SPACE:
						playerObj.fireDisabled = false;
					break;

					// Stops player movement
					case SDLK_UP:
						playerObj.yVelocity--;
					break;
					case SDLK_DOWN:
						playerObj.yVelocity--;
					break;
					case SDLK_LEFT:
						playerObj.yVelocity--;
					break;
					case SDLK_RIGHT:
						playerObj.yVelocity--;
					break;
					default:
					break;
				}
		
		}
	}
	

}

bool KeyboardHandler::isPressed(int keyCode) {
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	
	if (currentKeyStates[keyCode]) {
		return true;
	}
	else
		return false;
}		