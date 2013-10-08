#include "KeyboardHandler.h"

// Init quit as false
KeyboardHandler::KeyboardHandler(void)
{
		quitPressed = false;
		timeSinceLastUpdate = SDL_GetTicks();
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
					// Debug - spawn enemy
					renderer.pushIntoRenderQueue(new Enemy(Enemy::BENE,200));
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

	// Separate player shooting
	if(isPressed(SDL_SCANCODE_SPACE)) {
		// Only allows player to fire once per keypress
		if (!playerObj.fireDisabled && !playerObj.checkPowerUp(gameObject::POWERUP_MULTIFIRE)) {

			// Create a bullet and push it into the rendererqueue
			if (playerObj.checkPowerUp(gameObject::POWERUP_TRIAMMO)) {
				// Angled bullets
				gameObject* tempBullet = new bulletClass(playerObj.x+75, playerObj.y+20,1);
				gameObject* tempBullet2 = new bulletClass(playerObj.x+75, playerObj.y+40,1);
				tempBullet->setTarget(-10);
				tempBullet2->setTarget(490);

				renderer.pushIntoRenderQueue(tempBullet);
				renderer.pushIntoRenderQueue(tempBullet2);
				renderer.pushIntoRenderQueue(new bulletClass(playerObj.x+75, playerObj.y+30,1));
			}
			else {
			renderer.pushIntoRenderQueue(new bulletClass(playerObj.x+75, playerObj.y+30,1));
			}
			playerObj.fireDisabled = true;
		}
		else if(playerObj.checkPowerUp(gameObject::POWERUP_MULTIFIRE)) {
			// Set a delay for multifirebullets
			if (timeSinceLastUpdate < SDL_GetTicks()) {
				if (playerObj.checkPowerUp(gameObject::POWERUP_TRIAMMO)) {
					// Angled bullets
					gameObject* tempBullet = new bulletClass(playerObj.x+75, playerObj.y+20,1);
					gameObject* tempBullet2 = new bulletClass(playerObj.x+75, playerObj.y+40,1);
					tempBullet->setTarget(-10);
					tempBullet2->setTarget(490);

					renderer.pushIntoRenderQueue(tempBullet);
					renderer.pushIntoRenderQueue(tempBullet2);
					renderer.pushIntoRenderQueue(new bulletClass(playerObj.x+75, playerObj.y+30,1));
				}
				else {
					renderer.pushIntoRenderQueue(new bulletClass(playerObj.x+75, playerObj.y+30,1));
				}

				timeSinceLastUpdate = SDL_GetTicks() + 250;
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