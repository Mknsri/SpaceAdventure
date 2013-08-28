#include "Enemy.h"


Enemy::Enemy(enemyType eType)
{
	switch (eType) 
	{
		case MORP:
		break;
		case DORP:
			objectTexture = LoadImage("data\\dorp.png");
		break;
		case BENE:
		break;
		case MONSTRO:
		break;
	}

	y = 0;
	std::random_device rng;
	y = rng() % 480; 
	x = 670;
	maxSpeed = 5;

	collisionBuffer = 5;
	collisionEnabled = true;
}


Enemy::~Enemy(void)
{
}


int Enemy::updatePosition() {
	x -= 5;
	if (x < -10)
		deleteThis = true;

	return 0;
}

int Enemy::collisionEvent() {
	deleteThis = true;
	return 0;
}