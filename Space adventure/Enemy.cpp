#include "Enemy.h"


Enemy::Enemy(enemyType eType, int startY)
{

	
	explosionAnim = new Animation("data\\explosionanim.png",5,0,6);

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

	y = startY;
	// If starting height was not specified
	if (y != 0) {
		std::random_device rng;
		y = rng() % 460;
	}
	x = 690;
	maxSpeed = 5;

	collisionBuffer = 5;
	collisionEnabled = true;
	collisionDetected = false;
}


Enemy::~Enemy(void)
{
}


int Enemy::updatePosition() {
	x -= 5;
	if (x < -20)
		deleteThis = true;

	

	if (explosionAnim->animationPlaying() && collisionDetected == true) {
		objectTexture = nullptr;
		explosionAnim->playAnimationOnce();
	}
	else if ( explosionAnim->animationPlaying() == false && collisionDetected == true)
		deleteThis = true;


	return 0;
}

int Enemy::collisionEvent() {
	
	collisionDetected = true;
	return 0;
}