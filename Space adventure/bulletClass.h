#ifndef BULLET_H 
#define BULLET_H

#include "draw.h"
#include "gameObject.h"
#include "Animation.h"

#include <stdexcept>

class bulletClass : public gameObject
{
	public:
		// bullet creator, position(x,y) and direction (-1 Left, 1 right) as parameters
		bulletClass(int x, int y,  int bullDir);

		// Update per frame
		int updatePosition();

		// Collision event
		int collisionEvent();

		// Set bullet direction, takes y
		int bulletTargetY, bulletDirectionModifier;
		void setTarget(int targetY);

		~bulletClass();
};

#endif