#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "Animation.h"

#include <random>


class Enemy : public gameObject
{
public:

	// Enemy typs
	enum enemyType { MORP, DORP, BENE, MONSTRO };

	
	Animation *explosionAnim;

	// Constructor, enemy type as parameter and optional start position
	Enemy(enemyType eType, int startY = 0);
	~Enemy(void);

	// Collision event
	int collisionEvent();

	// Update per frame
	int updatePosition();
};


#endif
