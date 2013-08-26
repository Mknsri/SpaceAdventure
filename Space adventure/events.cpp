#include "events.h"

bool keyPressed = false;

int handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)	{
			return 0;
		}
		else if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_ESCAPE:
					return 0;
				break;
				case SDLK_RETURN:
					return 2;
				break;

				default:
				break;
			}
		}
		else {
			return 1;
		}
	}
	
	return 1;
}

int handleKeyboardEvents(playerClass* playerObj, rendererClass &renderer) {
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	{
		playerObj->y -= 5;
	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
	{
		playerObj->y += 5;
	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		playerObj->x -= 5;
	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		playerObj->x += 5;
	}
	if( currentKeyStates[ SDL_SCANCODE_SPACE ] ) {
		if (!keyPressed) {
			// Player fires
			playerObj->playerFire();
			//renderer.renderQueue.push_back(new bulletClass(playerObj->x, playerObj->y));
			keyPressed = true;
		}
	}
	else
	{
		return 1;
	}

	return 0;

}