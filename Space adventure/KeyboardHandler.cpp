#include "KeyboardHandler.h"


KeyboardHandler::KeyboardHandler(void)
{
		quitPressed = false;
}


KeyboardHandler::~KeyboardHandler(void)
{
}


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
					if (!playerObj.fireDisabled) {
						playerObj.playerFire();
						renderer.pushIntoRenderQueue(new bulletClass(playerObj.x, playerObj.y));
						playerObj.fireDisabled = true;
					}
				break;
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
				case SDLK_ESCAPE:
					quitPressed = true;
				break;
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
		else if(event.type == SDL_KEYUP ){
			switch(event.key.keysym.sym) {
					case SDLK_SPACE:
						playerObj.fireDisabled = false;
					break;
					case SDLK_UP:
						playerObj.yVelocity = 0;
					break;
					case SDLK_DOWN:
						playerObj.yVelocity = 0;
					break;
					case SDLK_LEFT:
						playerObj.xVelocity = 0;
					break;
					case SDLK_RIGHT:
						playerObj.xVelocity = 0;
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