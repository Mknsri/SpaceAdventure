#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "Animation.h"
#include "Motion.h"

#include <random>


class Enemy : public gameObject
{
public:

	// Enemy types
	enum enemyType { MORP, DORP, BENE, MONSTRO };
	enemyType enType;
	
	// Death animation
	Animation *explosionAnim;

	// Animation for enemy
	Animation *enemyAnim;
	
	// Motions for enemies
	Motion morpMotion;

	// ranges for animations
	int upRange, downRange;


	// Constructor, enemy type as parameter and optional start position
	Enemy(enemyType eType, int startY = 0);
	~Enemy(void);

	// Collision event
	int collisionEvent();

	// Update per frame
	int updatePosition();

	// Draws enemy - inherited from gameObject
	int drawObject();
};


#endif
