#ifndef POWERUP_H
#define POWERUP_H

#include "gameobject.h"

#include <random>

class PowerUp :	public gameObject
{
public:

	enum pUpType { HEALTH, TRIAMMO, MULTIFIRE };
	pUpType pupType;

	int collisionEvent();

	int updatePosition();

	PowerUp(pUpType ptype);
	~PowerUp(void);
};

#endif