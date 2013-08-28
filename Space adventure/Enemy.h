#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"

#include <random>


class Enemy : public gameObject
{
public:

	// Enemy typs
	enum enemyType { MORP, DORP, BENE, MONSTRO };

	// Constructor, enemy type as parameter
	Enemy(enemyType eType);
	~Enemy(void);

	// Collision event
	int collisionEvent();

	// Update per frame
	int updatePosition();
};


#endif
