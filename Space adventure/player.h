#ifndef PLAYER_H 
#define PLAYER_H

#include "gameObject.h"

// Player object
class playerClass : public gameObject 
{
	private:
		// Stats
		int health;
		

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
};

#endif
