#ifndef PLAYER_H 
#define PLAYER_H

#include "gameObject.h"

class playerClass : public gameObject 
{
	public:
		int health;
		bool fireDisabled;
		int yVelocity, xVelocity;

	playerClass();
	int collisionEvent();
	void playerFire();
	int updatePosition();
};

#endif
