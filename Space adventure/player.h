#ifndef PLAYER_H 
#define PLAYER_H

#include "gameObject.h"
#include "Animation.h"

// Player object
class playerClass : public gameObject 
{
	private:
		// Stats
		int health;
		bool alive;

		// Player animations
		Animation* playerAnimIdle;
		Animation* playerAnimHurt;
		Animation* playerAnimDeath;

		SDL_Texture* playerHealthIcon;

	public:

		playerClass();
		
		// If the player can fire
		bool fireDisabled;

		// Triggered if collisioncheck returns true
		int collisionEvent();

		// Player fires
		void playerFire();
		
		// Update per frame
		int updatePosition();

		// Draws player - inherited from gameObject
		int drawObject();

		// Check if player is alive
		bool isPlayerAlive();

		void newGame();

		// Player death
		void playerDeath();
};

#endif
