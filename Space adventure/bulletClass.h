#ifndef BULLET_H 
#define BULLET_H

#include "draw.h"
#include "file.h"
#include "gameObject.h"

#include <stdexcept>

class bulletClass : public gameObject
{
	public:
		bulletClass(int x, int y);

		int updatePosition();
		int collisionEvent();
		~bulletClass();
};

#endif