#ifndef PLAYER_H 
#define PLAYER_H

#include "textClass.h"
#include "gameObject.h"
#include "Animation.h"

// Player object
class playerClass : public gameObject 
{
	private:
		// Stats
		bool alive;
		int score;
		
	
		// Player score text
		textClass *scoreText;

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

		void setPowerUp(powerUps powerup);
		bool checkPowerUp(powerUps powerup);

		void newGame();

		// Player death
		void playerDeath();

		// Display players score
		void displayScore();

		void addScore(int points);

};

#endif
