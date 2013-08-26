#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"

#include <random>


class Enemy : public gameObject
{
public:
	enum enemyType { MORP, DORP, BENE, MONSTRO };
	Enemy(enemyType eType);
	~Enemy(void);

	int collisionEvent();
	int updatePosition();
};


#endif
