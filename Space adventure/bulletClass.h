#ifndef BULLET_H 
#define BULLET_H

#include "draw.h"
#include "file.h"
#include "gameObject.h"

#include <stdexcept>

class bulletClass : public gameObject
{
	public:
		// bullet creator, position(x,y) as parameters
		bulletClass(int x, int y);

		// Update per frame
		int updatePosition();

		// Collision event
		int collisionEvent();

		~bulletClass();
};

#endif